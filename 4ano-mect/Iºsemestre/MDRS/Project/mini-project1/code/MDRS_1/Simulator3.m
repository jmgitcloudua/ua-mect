function [PLD , PLV, APDD , APDV, MPDD , MPDV, TT] = Simulator3(lambda,C,f,P,n)
% INPUT PARAMETERS:
%  lambda - packet rate (packets/sec)
%  C      - link bandwidth (Mbps)
%  f      - queue size (Bytes)
%  P      - number of packets (stopping criterium)
% OUTPUT PARAMETERS:
%  PL   - packet loss (%)
%  APD  - average packet delay (milliseconds)
%  MPD  - maximum packet delay (milliseconds)
%  TT   - transmitted throughput (Mbps)

%Events:
ARRIVAL= 0;       % Arrival of a packet            
DEPARTURE= 1;     % Departure of a packet

%Packet Types
DATA = 0;
VOIP = 1;

%State variables:
STATE = 0;          % 0 - connection free; 1 - connection bysy
QUEUEOCCUPATION= 0; % Occupation of the queue (in Bytes)
QUEUE= [];          % Size and arriving time instant of each packet in the queue

%Statistical Counters:
TOTALDATAPACKETS= 0;            % No. of DATA packets arrived to the system
TOTALVOIPPACKETS= 0;            % No. of VOIP packets arrived to the system
LOSTDATAPACKETS= 0;             % No. of DATA packets dropped due to buffer overflow
LOSTVOIPPACKETS= 0;             % No. of VOIP packets dropped due to buffer overflow
TRANSMITTEDDATAPACKETS= 0;      % No. of DATA transmitted packets
TRANSMITTEDVOIPPACKETS= 0;      % No. of VOIP transmitted packets
DATADELAYS= 0;                  % Sum of the delays of DATA packets
VOIPDELAYS= 0;                  % Sum of the delays of VOIP packets
MAXDATADELAY= 0;                % Maximum delay among all DATA packets
MAXVOIPDELAY= 0;                % Maximum delay among all VOIP packets
TRANSMITTEDBYTES= 0;            % Sum of the Bytes of transmitted packets

% Initializing the simulation clock:
Clock= 0;

% Initializing the List of Events with the first ARRIVAL:
tmp= Clock + exprnd(1/lambda);
EventList = [ARRIVAL, tmp, GeneratePacketSize(), tmp, DATA];

for i=1:n
    tmpVoip = Clock + GenerateVOIPPacketsTime();
    EventList = [EventList; ARRIVAL, tmpVoip, GenerateVOIPPacketSize(), tmpVoip, VOIP];
end

%Similation loop:
while TRANSMITTEDVOIPPACKETS + TRANSMITTEDDATAPACKETS < P               % Stopping criterium
    EventList= sortrows(EventList,2);    % Order EventList by time
    Event= EventList(1,1);               % Get first event and 
    Clock= EventList(1,2);               %   and
    PacketSize= EventList(1,3);          %   associated
    ArrivalInstant= EventList(1,4);      %   parameters.
    PacketType = EventList(1,5);         %
    EventList(1,:)= [];                  % Eliminate first event
    switch Event
        case ARRIVAL                     % If first event is an ARRIVAL
            if PacketType == DATA
                TOTALDATAPACKETS = TOTALDATAPACKETS + 1;
                tmp = Clock + exprnd(1/lambda);
                EventList = [EventList; ARRIVAL, tmp, GeneratePacketSize(), tmp, DATA];
            else
                TOTALVOIPPACKETS = TOTALVOIPPACKETS + 1;
                tmpVoip = Clock + GenerateTimeBetweenVOIPPackets();
                EventList = [EventList; ARRIVAL, tmpVoip, GenerateVOIPPacketSize(), tmpVoip, VOIP];
            end
            
            if STATE==0
                STATE = 1;
                EventList = [EventList; DEPARTURE, Clock + 8*PacketSize/(C*10^6), PacketSize, Clock, PacketType];
            else
                if QUEUEOCCUPATION + PacketSize <= f
                    QUEUE = [QUEUE;PacketSize , Clock, PacketType];
                    QUEUEOCCUPATION = QUEUEOCCUPATION + PacketSize;
                elseif PacketType == DATA
                    LOSTDATAPACKETS = LOSTDATAPACKETS + 1;
                else
                    LOSTVOIPPACKETS = LOSTVOIPPACKETS + 1;
                end
            end
        case DEPARTURE                     % If first event is a DEPARTURE
            TRANSMITTEDBYTES = TRANSMITTEDBYTES + PacketSize;

            if PacketType == DATA
                DATADELAYS = DATADELAYS + (Clock - ArrivalInstant);
                if Clock - ArrivalInstant > MAXDATADELAY
                    MAXDATADELAY = Clock - ArrivalInstant;
                end

                TRANSMITTEDDATAPACKETS = TRANSMITTEDDATAPACKETS + 1;
            else
                VOIPDELAYS = VOIPDELAYS + (Clock - ArrivalInstant);
                if Clock - ArrivalInstant > MAXVOIPDELAY
                    MAXVOIPDELAY = Clock - ArrivalInstant;
                end

                TRANSMITTEDVOIPPACKETS = TRANSMITTEDVOIPPACKETS + 1;
            end

            if QUEUEOCCUPATION > 0
                EventList = [EventList; DEPARTURE, Clock + 8*QUEUE(1,1)/(C*10^6), QUEUE(1,1), QUEUE(1,2), QUEUE(1,3)];
                QUEUEOCCUPATION= QUEUEOCCUPATION - QUEUE(1,1);
                QUEUE(1,:)= [];
            else
                STATE= 0;
            end
    end
end

%Performance parameters determination:
PLD= 100*LOSTDATAPACKETS/TOTALDATAPACKETS;      % in %
PLV= 100*LOSTVOIPPACKETS/TOTALVOIPPACKETS;      % in %
APDD= 1000*DATADELAYS/TRANSMITTEDDATAPACKETS;   % in milliseconds
APDV= 1000*VOIPDELAYS/TRANSMITTEDVOIPPACKETS;   % in milliseconds
MPDD= 1000*MAXDATADELAY;                    % in milliseconds
MPDV= 1000*MAXVOIPDELAY;                    % in milliseconds
TT= 10^(-6)*TRANSMITTEDBYTES*8/Clock;  % in Mbps

end

function out= GeneratePacketSize()
    aux= rand();
    aux2= [65:109 111:1517];
    if aux <= 0.19
        out= 64;
    elseif aux <= 0.19 + 0.23
        out= 110;
    elseif aux <= 0.19 + 0.23 + 0.17
        out= 1518;
    else
        out = aux2(randi(length(aux2)));
    end
end

function out= GenerateVOIPPacketSize()
    out = randi([110 130]);
end

function out= GenerateVOIPPacketsTime()
    out = unifrnd(0, 0.02);
end

function out= GenerateTimeBetweenVOIPPackets()
    out = unifrnd(0.016, 0.024);
end
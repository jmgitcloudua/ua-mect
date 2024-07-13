CREATE SCHEMA ReservaVoos;
GO

CREATE TABLE ReservaVoos.AIRPORT(
	Airport_Code    char(15)    NOT NULL,
    City            varchar(30) UNIQUE NOT NULL,
    Name            varchar(30) NOT NULL,
    State           varchar(30) NOT NULL,
    PRIMARY KEY (Airport_Code)
);

CREATE TABLE ReservaVoos.AirPlane_Type(
    Type_Name       varchar(30) NOT NULL,
    Company         varchar(30) NOT NULL,
    Max_Seats       int          NOT NULL CHECK (Max_Seats > 0),
    PRIMARY KEY (Type_Name)
);

CREATE TABLE ReservaVoos.AirPlane(
    AirPlane_ID         char(9)          NOT NULL,
    Type_Name           varchar(30)  NOT NULL,
    Total_no_of_seats    char(15)     NOT NULL CHECK (Total_no_of_seats > 0),
    PRIMARY KEY (AirPlane_ID),
    FOREIGN KEY (Type_Name) REFERENCES ReservaVoos.AirPlane_Type(Type_Name),
);

CREATE TABLE ReservaVoos.Flight(
    Number_of_Flight    int    NOT NULL CHECK (Number_of_Flight > 0),
    Airline             char(9)     NOT NULL,
    Weekdays            int         ,
    PRIMARY KEY (Number_of_Flight)
);

CREATE TABLE ReservaVoos.Flight_Leg(
    Flight_Number           int    NOT NULL CHECK (Flight_Number > 0),
    Leg_no                  int    NOT NULL CHECK (Leg_no > 0),
    Airport_Code_Depart     char(15)    NOT NULL,
    Airport_Code_Arrival    char(15)    NOT NULL,
    Scheduled_Departure_Time      date    NOT NULL,
    Scheduled_Arrival_Time        date    NOT NULL,
    PRIMARY KEY (Leg_no),
    FOREIGN KEY (Flight_Number) REFERENCES ReservaVoos.Flight(Number_of_Flight),
    FOREIGN KEY (Airport_Code_Depart) REFERENCES ReservaVoos.Airport(Airport_Code),
    FOREIGN KEY (Airport_Code_Arrival) REFERENCES ReservaVoos.Airport(Airport_Code),
    check (Scheduled_Departure_Time < Scheduled_Arrival_Time),
);

CREATE TABLE ReservaVoos.Leg_Instance(
    Flight_Number       int          NOT NULL,
    Leg_no              int           NOT NULL CHECK (Leg_no > 0),
    Seat_no            char(3)     NOT NULL CHECK (Seat_no > 0),
    Date_of_flight     date         NOT NULL,
    Depart_Airport     char(15)     NOT NULL,
    Arrival_Airport    char(15)     NOT NULL,
    Depart_Time        time         NOT NULL,
    Arrival_Time       time         NOT NULL,
    Number_of_available_seats int NOT NULL CHECK (Number_of_available_seats >= 0),
    PRIMARY KEY (Flight_Number, Leg_no, Date_of_flight),
    FOREIGN KEY (Leg_no) REFERENCES ReservaVoos.Flight_Leg(Leg_no),
    FOREIGN KEY (Flight_Number) REFERENCES ReservaVoos.Flight(Number_of_Flight)

);

CREATE TABLE    ReservaVoos.Seat(
    Seat_no            char(3)          NOT NULL,
    Date_of_flight     date             NOT NULL,
    Leg_no             int              NOT NULL,
    Flight_Number      int              NOT NULL,
    Customer_Name      varchar(30)      NOT NULL,
    Cphone_Number      int              ,
    PRIMARY KEY (Seat_no, Date_of_flight, Leg_no, Flight_Number),
    FOREIGN KEY (Flight_Number,Leg_no, Date_of_flight) REFERENCES ReservaVoos.Leg_Instance(Flight_Number,Leg_no, Date_of_flight)
);

CREATE TABLE ReservaVoos.Can_Land(
    Airport_code        char(15)     NOT NULL,
    Type_Name           varchar(30)  NOT NULL,
    PRIMARY KEY (Airport_code, Type_Name),
    FOREIGN KEY (Airport_code) REFERENCES ReservaVoos.Airport(Airport_Code),
    FOREIGN KEY (Type_Name) REFERENCES ReservaVoos.AirPlane_Type(Type_Name)

);

CREATE TABLE ReservaVoos.Fare(
    Flight_Number       int             NOT NULL CHECK (Flight_Number > 0),
    Code_Fare            char(3)        NOT NULL,
    Amount               int            NOT NULL CHECK (Amount > 0),
    Restrictions         varchar(30)    NOT NULL,
    PRIMARY KEY (Code_Fare),
    FOREIGN KEY (Flight_Number) REFERENCES ReservaVoos.Flight(Number_of_Flight)
);

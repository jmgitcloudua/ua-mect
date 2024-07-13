% calculates Availability of a path
function avail = calculateAvailability(Availability, path)
    avail = 1;
    for i = 1:(length(path) - 1)
        avail = avail * Availability(path(i), path(i+1));
    end
end
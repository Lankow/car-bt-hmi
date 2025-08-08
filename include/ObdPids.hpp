#ifndef OBDPIDS_HPP
#define OBDPIDS_HPP

    // Centralized OBD-II PID definitions.
    // Add new PIDs here to keep them consistent across the project.

    namespace ObdPids {
    inline constexpr const char VEHICLE_SPEED[] = "010D";  // Vehicle Speed
    inline constexpr const char ENGINE_RPM[] = "010C";     // Engine RPM

    inline constexpr const char VEHICLE_SPEED_RESP[] = "41 0D";  // Vehicle Speed Response
    inline constexpr const char ENGINE_RPM_RESP[] = "41 0C";     // Engine RPM Response

}

#endif // OBDPIDS_HPP

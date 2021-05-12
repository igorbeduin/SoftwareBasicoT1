#pragma once

class ControlVariables 
{
    public:
        static bool quitRequest;
        static void set_quitRequest(bool request);
        static bool get_quitRequest();
};
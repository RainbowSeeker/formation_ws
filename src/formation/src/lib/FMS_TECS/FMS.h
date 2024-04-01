#pragma once

#include "src/FMS_TECS.h"

/*
    Pilot_Cmd_Bus Pilot_Cmd;           // '<Root>/Pilot_Cmd'
    Mission_Data_Bus Mission_Data;     // '<Root>/Mission_Data'
    INS_Out_Bus INS_Out;               // '<Root>/INS_Out'
    Formation_Cross_Bus Formation_Cross;// '<Root>/Formation_Cross'
    */
using FMS_In = FMS_TECS::ExtU_FMS_TECS_T;

/*
    real32_T att_cmd[2];               // '<Root>/att_cmd'
    real32_T throttle_cmd;             // '<Root>/throttle_cmd'
    Other_Mission_Data_Bus Other_Mission_Data;// '<Root>/Other_Mission_Data'
    real32_T Form_Single;              // '<Root>/Form_Single'
*/
using FMS_Out = FMS_TECS::ExtY_FMS_TECS_T;


class FMS
{
public:
    FMS() {};
    ~FMS(){};

    void initialize()
    {
        _fms.initialize();
    }

    const FMS_Out &step(const FMS_In *fms_in)
    {
        _fms.setExternalInputs(fms_in);
        _fms.step();
        return _fms.getExternalOutputs();
    }

private:
    FMS_TECS _fms;
};

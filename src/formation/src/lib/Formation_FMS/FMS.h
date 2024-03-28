#pragma once

#include "src/Formation_FMS.h"
#include "src/Formation_FMS_types.h"

/*
    Pilot_Cmd_Bus Pilot_Cmd;           // '<Root>/Pilot_Cmd'
    Mission_Data_Bus Mission_Data;     // '<Root>/Mission_Data'
    INS_Out_Bus INS_Out;               // '<Root>/INS_Out'
    Formation_Cross_Bus Formation_Cross;// '<Root>/Formation_Cross'
    */
using FMS_In = Formation_FMS::ExtU_Formation_FMS_T;

/*
    FMS_Out_Bus FMS_Out;               // '<Root>/FMS_Out'
    Other_Mission_Data_Bus Other_Mission_Data;// '<Root>/Other_Mission_Data'
    real32_T Form_Single;              // '<Root>/Form_Single'
*/
using FMS_Out = Formation_FMS::ExtY_Formation_FMS_T;


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
    Formation_FMS _fms;
};

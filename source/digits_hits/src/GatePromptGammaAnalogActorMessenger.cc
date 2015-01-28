/*----------------------
  GATE version name: gate_v7

  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See GATE/LICENSE.txt for further details
  ----------------------*/

#include "GateConfiguration.h"
#include "GatePromptGammaTLEActor.hh"
#include "GatePromptGammaAnalogActor.hh"

//-----------------------------------------------------------------------------
GatePromptGammaAnalogActor::
GatePromptGammaAnalogActor(GatePromptGammaTLEActor* v)
:GateImageActorMessenger(v), pTLEActor(v)
{
  BuildCommands(baseName+pActor->GetObjectName());
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
GatePromptGammaAnalogActor::~GatePromptGammaAnalogActor()
{
  DD("GatePromptGammaAnalogActor destructor");
  delete pSetInputDataFileCmd;
  delete pEnableUncertaintyCmd;
  delete pEnableIntermediaryUncertaintyOutputCmd;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void GatePromptGammaAnalogActor::BuildCommands(G4String base)
{
  G4String bb = base+"/setInputDataFile";
  pSetInputDataFileCmd = new G4UIcmdWithAString(bb, this);
  G4String guidance = G4String("Set input root filename with proton/gamma energy 2D spectrum (obtained from PromptGammaStatisticsActor).");
  pSetInputDataFileCmd->SetGuidance(guidance);

  bb = base+"/enableUncertainty";
  pEnableUncertaintyCmd = new G4UIcmdWithABool(bb, this);
  guidance = G4String("Enable uncertainty output (per voxel per E_gamma).");
  pEnableUncertaintyCmd->SetGuidance(guidance);

  bb = base+"/enableIntermediaryUncertaintyOutput";
  pEnableIntermediaryUncertaintyOutputCmd = new G4UIcmdWithABool(bb, this);
  guidance = G4String("Enable outputs to calculate uncertainty post process. Output is Gamma_m database, and L and L^2 per voxel per proton energy.");
  pEnableIntermediaryUncertaintyOutputCmd->SetGuidance(guidance);

}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void GatePromptGammaAnalogActor::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
  if (cmd == pSetInputDataFileCmd) pTLEActor->SetInputDataFilename(newValue);
  if (cmd == pEnableUncertaintyCmd) pTLEActor->EnableUncertaintyImage(pEnableUncertaintyCmd->GetNewBoolValue(newValue));
  if (cmd == pEnableIntermediaryUncertaintyOutputCmd) pTLEActor->EnableIntermediaryUncertaintyOutput(pEnableIntermediaryUncertaintyOutputCmd->GetNewBoolValue(newValue));
  GateImageActorMessenger::SetNewValue(cmd,newValue);
}
//-----------------------------------------------------------------------------

#pragma once

#include <Homie.h>

const char VALUE[] = "value";
const char UNIT[] = "unit";

class SensorNode : HomieNode
{
public:
  SensorNode(const char* id, const char* unit);
  void setValue(const String& value);
  bool setUnit(const char* unit);
private:
  void onReadyToOperate();
  char* node_unit;
  bool unitSent;
};

SensorNode::SensorNode(const char* id, const char* unit): HomieNode(id, "sensor")
{
  node_unit = unit;
  advertise(VALUE);
  advertise(UNIT);
  unitSent = false;
}

void SensorNode::onReadyToOperate(){
  setProperty(UNIT).send(node_unit);
  unitSent = true;
}

void SensorNode::setValue(const String& value){
  setProperty(VALUE).send(value);
}


void SensorNode::setUnit(const char* unit){
  if (unitSent) return false;
  node_unit = unit;
  return true;
}

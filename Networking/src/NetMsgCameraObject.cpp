#include <sstream>

#include "NetMsgCameraObject.h"
#include "ManagerEnvironmentConfiguration.h"
#include "ManagerGLView.h"
#include "GLViewNetworking.h"
#include "WorldContainer.h"

using namespace Aftr;

NetMsgMacroDefinition(NetMsgCameraObject);

bool NetMsgCameraObject::is_inserted = false;
WO* NetMsgCameraObject::object = nullptr;

// Memory handling
/*NetMsgCameraObject::~NetMsgCameraObject() {
	delete object;
}*/

// Send location as payload
bool NetMsgCameraObject::toStream(NetMessengerStreamBuffer& os) const {
	os << location.x << location.y << location.z;
	return true;
}

// Receive location as payload
bool NetMsgCameraObject::fromStream(NetMessengerStreamBuffer& is) {
	is >> location.x >> location.y >> location.z;
	return true;
}

// Update position, and add to world if it isn't already
void NetMsgCameraObject::onMessageArrived() {\
	// This check is needed to actually initialize object due to manager dependencies
	if (object == nullptr) object = WO::New(ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl", Vector(1, 1, 1));
	object->setPosition(location);
	if (!is_inserted) {
		ManagerGLView::getGLView()->getWorldContainer()->push_back(object);
		is_inserted = true;
	}
}

// For debug purposes
std::string NetMsgCameraObject::toString() const {
	std::stringstream ss;

	ss << NetMsg::toString();
	ss << "  Payload: \n"
		<< "Position: x = " << location.x << " y = " << location.y << " z = " << location.z << "\n";
	return ss.str();
}

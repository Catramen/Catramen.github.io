#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include "ppapi/c/pp_input_event.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/size.h"
#include "ppapi/cpp/view.h"
#include "ppapi/utility/graphics/paint_manager.h"
#include <string>

/// The Instance class.  One of these exists for each instance of your NaCl
/// module on the web page.  The browser will ask the Module object to create
/// a new Instance for each occurrence of the <embed> tag that has these
/// attributes:
///     src="hello_tutorial.nmf"
///     type="application/x-pnacl"
/// To communicate with the browser, you must override HandleMessage() to
/// receive messages from the browser, and use PostMessage() to send messages
/// back to the browser.  Note that this interface is asynchronous.
class NaclLoggerInstance : public pp::Instance {
public:
  /// The constructor creates the plugin-side instance.
  /// @param[in] instance the handle to the browser-side plugin instance.
  explicit NaclLoggerInstance(PP_Instance instance) : pp::Instance(instance), mousedown_(false), touchdown_(false)
  {
      RequestInputEvents(PP_INPUTEVENT_CLASS_MOUSE | PP_INPUTEVENT_CLASS_TOUCH);
      PostMessage("red");
      PostMessage("nacl module loaded");
  }
  virtual ~NaclLoggerInstance() {}

  /// Handler for messages coming in from the browser via postMessage().  The
  /// @a var_message can contain be any pp:Var type; for example int, string
  /// Array or Dictinary. Please see the pp:Var documentation for more details.
  /// @param[in] var_message The message posted by the browser.
  virtual void HandleMessage(const pp::Var& var_message) {
    // TODO(sdk_user): 1. Make this function handle the incoming message.
    // Ignore the message if it is not a string.
    if (!var_message.is_string())
      return;

    // Get the string message and compare it to "hello".
    // PostMessage("red");
    // PostMessage("var_reply");
    // PostMessage("blue");
    // PostMessage("var_reply");
  }
  virtual bool HandleInputEvent(const pp::InputEvent& event) {
          //     PostMessage("red");
          // PostMessage(std::to_string(static_cast<int>(event.GetType())));

    switch (event.GetType()) {
      // case PP_INPUTEVENT_TYPE_MOUSEDOWN: {
      //   mousedown_ = true;
      //   return true;
      // }
      case PP_INPUTEVENT_TYPE_MOUSEMOVE: {
        pp::MouseInputEvent mouse_event(event);
        //if (mousedown_) {
          PostMessage("red");
          PostMessage("MouseMove Event x: " + std::to_string(static_cast<int>(mouse_event.GetPosition().x())) + 
            " y: "+ std::to_string(static_cast<int>(mouse_event.GetPosition().y())));
        //}
      }
      case  PP_INPUTEVENT_TYPE_MOUSEUP: {
        mousedown_ = ! mousedown_;
        return true;
      }
      case PP_INPUTEVENT_TYPE_TOUCHSTART: {
        // pp::TouchInputEvent touch(event);
        // // Update the square on a touch down.
        // uint32_t count = touch.GetTouchCount(PP_TOUCHLIST_TYPE_CHANGEDTOUCHES);
        // for (uint32_t i = 0; i < count; ++i) {
        //   pp::TouchPoint point = touch.GetTouchByIndex(
        //     PP_TOUCHLIST_TYPE_CHANGEDTOUCHES, i);
        //   UpdateSquare(static_cast<int>(point.position().x()),
        //    static_cast<int>(point.position().y()));
        // }
        // return true;
      }
      case PP_INPUTEVENT_TYPE_TOUCHMOVE:
      case PP_INPUTEVENT_TYPE_TOUCHEND:
      case PP_INPUTEVENT_TYPE_TOUCHCANCEL:
      return true;

      default:
      return false;
    }
  }
private:
  bool mousedown_;
  bool touchdown_;
};

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with type="application/x-pnacl".
class NaclLoggerlModule : public pp::Module {
public:
  NaclLoggerlModule() : pp::Module() {  }
  virtual ~NaclLoggerlModule() {}

  /// Create and return a HelloTutorialInstance object.
  /// @param[in] instance The browser-side instance.
  /// @return the plugin-side instance.
  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new NaclLoggerInstance(instance);
  }
};

namespace pp {
/// Factory function called by the browser when the module is first loaded.
/// The browser keeps a singleton of this module.  It calls the
/// CreateInstance() method on the object you return to make instances.  There
/// is one instance per <embed> tag on the page.  This is the main binding
/// point for your NaCl module with the browser.
  Module* CreateModule() {
    return new NaclLoggerlModule();
  }
}  // namespace pp

#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework {
	using OnChangeCallback = void(*)(Keyboard &keyboard, KeyboardEvent &event);

	struct Coord {
		u32 wX;
		u32 wY;
	};

	class FUNCT {
    	public:
        	FUNCT(u32 Address) {
				ItemFunc = Address;
			};

			template <typename T, class ...Args>
			T Call(Args ...args) {
				return((T(*)(Args...))(ItemFunc))(args...);
			};

    	private:
        	u32 ItemFunc;
	};
	
	struct WrapLoc {
		u32 Address;
		u32 Lenght;
	};

	enum ExHandler {
		SUCCESS,
		ERROR_OP, //error opening file
		ERROR_DRD, //dump/restore/delete error
		ERROR_LI, //error listing
		ERROR_UN, //Unexcpected error
	};

	namespace Wrap {
		ExHandler	Dump(const std::string& path, std::string& filename, const std::string& filetype, WrapLoc dump, ...);
		ExHandler	Restore(const std::string& path, const std::string& filetype, const std::string& KBMsg, OnChangeCallback cb, WrapLoc rest, ...); 
		ExHandler	Delete(const std::string& path, const std::string& filetype);

		template<typename T>
		bool 		KB(const std::string &msg, bool hex, const int length, T &output, T def, OnChangeCallback cb = nullptr) {
			Sleep(Milliseconds(100));
			Keyboard kb(msg);
			kb.IsHexadecimal(hex);
			kb.SetMaxLength(length);
			kb.OnKeyboardEvent(cb);
			return kb.Open((T &)output, (T)def) == 0;
		}
	}
}
#endif
#pragma once

#include <CTRPluginFramework.hpp>
#include <type_traits>

#define TID_USA 		0x000400000014F100
#define TID_EUR 		0x000400000014F200
#define TID_JPN 		0x000400000014F000

namespace CTRPluginFramework {
	class Address {
		public:
			enum Region {
				USA = 0,
				EUR,
				JPN,
			};

			Address(void);

			Address(u32 address);

			static Address decodeARMBranch(const u32 src, const u32 val);

			static bool IsRegion(Region region);

            static std::string LoadRegion(void);

			u32 addr;
			u32 origVal;

            static std::string regionName;
			static Region regionId;

			Address MoveOffset(u32 offset);
			bool Patch(u32 newValue);
			bool Unpatch(void);
			bool IsPatched(void);

			template <typename T>
			bool Write(T newValue) {
				if constexpr (std::is_same_v<T, u32>) {
					return Patch(newValue);
				}
				else if constexpr (std::is_same_v<T, u16>) {
					return Process::Write16(addr, newValue);
				}
				else if constexpr (std::is_same_v<T, u8>) {
					return Process::Write8(addr, newValue);
				}
				else if constexpr (std::is_same_v<T, float>) {
					return Process::WriteFloat(addr, newValue);
				}
				else if constexpr (std::is_same_v<T, u64>) {
					return Process::Write64(addr, newValue);
				}
				else return false;
			};

			template <typename T, class ...Args>
			T Call(Args ...args) {
				return((T(*)(Args...))(addr))(args...);
			};
		private:
		 	void SetAddressData(u32 address);
			static std::unordered_map<u32, u32> origValList;
	};
}
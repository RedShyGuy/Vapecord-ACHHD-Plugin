#pragma once

#include <CTRPluginFramework.hpp>
#include <vector>
#include <initializer_list>

namespace CTRPluginFramework {
	using OnChangeCallback = void(*)(Keyboard &keyboard, KeyboardEvent &event);

	struct MemoryRange {
		u32 *address;
		int length;
	};

	enum class OperationResult {
		Success,
		OpenFailed,
		TransferFailed,
		ListingFailed,
		Aborted,
	};

	// Usage quick guide:
	// 1) Backup:
	//    PluginUtils::Backup::DumpMemory(path, filename, ".dat", { {address, length} });
	//    PluginUtils::Backup::RestoreMemory(path, ".dat", "Select file", { {address, length} });
	//    PluginUtils::Backup::DeleteBackup(path, ".dat");
	//
	// 2) Input:
	//    u32 value = 0;
	//    PluginUtils::Input::PromptNumber<u32>({ "Enter value", true, 8, value }, value);
	//
	// 3) Branch:
	//    u32 instruction = PluginUtils::Branch::CalculateBranchInstruction(pc, target);
	//    u32 target = PluginUtils::Branch::GetBranchTarget(pc, instruction);
	//
	// Notes:
	// - MemoryRange length is in bytes.
	// - Backup operations return OperationResult.
	namespace PluginUtils {
		namespace Backup {
			struct DumpOptions {
				bool showMessages{true};
				bool showRangeNotifications{false};
			};

			struct RestoreOptions {
				OnChangeCallback onSelectionChange{nullptr};
				bool showMessages{true};
			};

			struct DeleteOptions {
				bool showMessages{true};
			};

			OperationResult DumpMemory(
				const std::string &path,
				const std::string &filename,
				const std::string &filetype,
				const std::vector<MemoryRange> &ranges,
				const DumpOptions &options = {}
			);

			OperationResult DumpMemory(
				const std::string &path,
				const std::string &filename,
				const std::string &filetype,
				std::initializer_list<MemoryRange> ranges,
				const DumpOptions &options = {}
			);

			OperationResult RestoreMemory(
				const std::string &path,
				const std::string &filetype,
				const std::string &selectionMessage,
				const std::vector<MemoryRange> &ranges,
				const RestoreOptions &options = {}
			);

			OperationResult RestoreMemory(
				const std::string &path,
				const std::string &filetype,
				const std::string &selectionMessage,
				std::initializer_list<MemoryRange> ranges,
				const RestoreOptions &options = {}
			);

			OperationResult DeleteBackup(
				const std::string &path,
				const std::string &filetype,
				const DeleteOptions &options = {}
			);

			extern Directory restoreDirectory;
		}

		namespace Input {
			template<typename T>
			struct NumericPrompt {
				std::string message;
				bool hexadecimal;
				int maxLength;
				T defaultValue;
				OnChangeCallback onChange{nullptr};
			};

			template<typename T>
			bool PromptNumber(const NumericPrompt<T> &prompt, T &output) {
				Keyboard kb(prompt.message);
				kb.IsHexadecimal(prompt.hexadecimal);
				kb.SetMaxLength(prompt.maxLength);
				kb.OnKeyboardEvent(prompt.onChange);
				return kb.Open((T &)output, (T)prompt.defaultValue) == 0;
			}
		}

		namespace Branch {
			u32 CalculateBranchInstruction(u32 PC, u32 target);

			u32 GetBranchTarget(u32 PC, u32 instruction);

			s32 CalculateThumbBLXOffset(u32 branchAddress, u32 targetAddress);

			u32 EncodeThumbBLXInstruction(u32 branchAddress, u32 targetAddress);
		}
	}

	Process::ExceptionCallbackState CustomExceptionHandler(ERRF_ExceptionInfo* excep, CpuRegisters* regs);
}
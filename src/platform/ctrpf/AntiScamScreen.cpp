#include "core/Config.hpp"
#include "core/infrastructure/Language.hpp"
#include "Files.h"

namespace CTRPluginFramework {
    namespace {
        static const Color kBgPurple        (28,  20,  52);     //deep purple background
        static const Color kHeaderPurple    (100, 50,  170);    //purple header bar
        static const Color kHeaderHighlight (140, 80,  200);    //lighter purple accent on header
        static const Color kContentBg       (40,  28,  72);     //slightly lighter purple for content
        static const Color kFooterPurple    (48,  36,  64);     //dark purple-tinted footer bar
        static const Color kSeparator       (140, 90,  200);    //thin separator line colour
        static const Color kTextLight       (210, 200, 230);    //secondary/dimmed text
        static const Color kAccentLilac     (180, 130, 255);    //lilac accent (link/highlight)
        static const Color kWarningYellow   (255, 210, 60);     //! icon colour
        static const Color kButtonFill      (90,  50,  150);    //A-button prompt bg

        static constexpr u32 kTopW  = 400;
        static constexpr u32 kTopH  = 240;
        static constexpr u32 kBotW  = 320;
        static constexpr u32 kBotH  = 240;

        static void DrawCenteredSysfont(const Screen &scr, const std::string &text, u32 y, const Color &color, u32 screenWidth) {
            u32 textW = Screen::SystemFontSize(text.c_str());
            u32 x = (textW < screenWidth) ? (screenWidth - textW) / 2 : 4;
            scr.DrawSysfont(text, x, y, color);
        }

        static u32 DecodeUTF8(const std::string &s, size_t &i) {
            u8 c = static_cast<u8>(s[i]);
            u32 cp;
            size_t len;
            if (c < 0x80) { 
                cp = c; 
                len = 1; 
            } else if (c < 0xE0) { 
                cp = c & 0x1F; 
                len = 2; 
            } else if (c < 0xF0) { 
                cp = c & 0x0F; 
                len = 3; 
            } else { 
                cp = c & 0x07; 
                len = 4; 
            }

            for (size_t j = 1; j < len && (i + j) < s.size(); ++j) {
                cp = (cp << 6) | (static_cast<u8>(s[i + j]) & 0x3F);
            }
            
            i += len;
            return cp;
        }

        static bool IsCJKCodepoint(u32 cp) {
            return (cp >= 0x3000 && cp <= 0x303F)   //CJK Symbols and Punctuation
                || (cp >= 0x3040 && cp <= 0x309F)   //Hiragana
                || (cp >= 0x30A0 && cp <= 0x30FF)   //Katakana
                || (cp >= 0x3400 && cp <= 0x4DBF)   //CJK Extension A
                || (cp >= 0x4E00 && cp <= 0x9FFF)   //CJK Unified Ideographs
                || (cp >= 0xF900 && cp <= 0xFAFF)   //CJK Compatibility Ideographs
                || (cp >= 0xFF00 && cp <= 0xFFEF);  //Fullwidth Forms
        }

        static u32 DrawWrappedCentered(const Screen &scr, const std::string &text, u32 y, const Color &color, u32 screenWidth, u32 margin, u32 lineSpacing = 16) {
            u32 maxW = screenWidth - 2 * margin;
            std::string line;

            struct Token { 
                std::string text; 
                bool spaceBefore; 
            };
            std::vector<Token> tokens;
            std::string word;
            size_t i = 0;

            while (i < text.size()) {
                size_t start = i;
                u32 cp = DecodeUTF8(text, i);
                if (cp == ' ') {
                    if (!word.empty()) {
                        tokens.push_back({word, true});
                        word.clear();
                    }
                } else if (IsCJKCodepoint(cp)) {
                    if (!word.empty()) {
                        tokens.push_back({word, true});
                        word.clear();
                    }
                    tokens.push_back({text.substr(start, i - start), false});
                } else {
                    word += text.substr(start, i - start);
                }
            }

            if (!word.empty()) {
                tokens.push_back({word, true});
            }

            auto flushLine = [&]() {
                if (!line.empty()) {
                    DrawCenteredSysfont(scr, line, y, color, screenWidth);
                    y += lineSpacing;
                    line.clear();
                }
            };

            for (const auto &tok : tokens) {
                std::string candidate = line;
                if (!candidate.empty() && tok.spaceBefore) {
                    candidate += ' ';
                }

                candidate += tok.text;
                if (Screen::SystemFontSize(candidate.c_str()) <= maxW) {
                    line = candidate;
                } else {
                    flushLine();
                    line = tok.text;
                }
            }
            flushLine();
            return y;
        }

        static void DrawTopScreen(const Screen &scr) {
            auto *lang = Language::getInstance();
            scr.DrawRect(0, 0, kTopW, kTopH, kBgPurple);

            scr.DrawRect(0, 0, kTopW, 30, kHeaderPurple);
            scr.DrawRect(0, 28, kTopW, 2, kHeaderHighlight);

            DrawCenteredSysfont(scr, lang->get(TextID::SCAM_TITLE), 6, kWarningYellow, kTopW);

            constexpr u32 boxX = 15, boxY = 37;
            constexpr u32 boxW = kTopW - 2 * boxX, boxH = 164;
            scr.DrawRect(boxX, boxY, boxW, boxH, kContentBg);

            scr.DrawRect(boxX, boxY, boxW, 1, kSeparator);
            scr.DrawRect(boxX, boxY + boxH - 1, boxW, 1, kSeparator);
            scr.DrawRect(boxX, boxY, 1, boxH, kSeparator);
            scr.DrawRect(boxX + boxW - 1, boxY, 1, boxH, kSeparator);

            u32 ty = boxY + 10;
            ty = DrawWrappedCentered(scr, lang->get(TextID::SCAM_BODY1), ty, Color::White, kTopW, boxX + 8, 18);
            ty += 8;
            ty = DrawWrappedCentered(scr, lang->get(TextID::SCAM_BODY2), ty, kTextLight, kTopW, boxX + 8, 18);
            ty += 6;
            DrawCenteredSysfont(scr, DISCORDINV, ty, kAccentLilac, kTopW);

            scr.DrawRect(0, kTopH - 32, kTopW, 32, kFooterPurple);
            scr.DrawRect(0, kTopH - 32, kTopW, 1, kSeparator);

            DrawCenteredSysfont(scr, lang->get(TextID::SCAM_CONTINUE), kTopH - 24, Color::White, kTopW);
        }

        static void DrawBottomScreen(const Screen &src) {
            auto *lang = Language::getInstance();
            src.DrawRect(0, 0, kBotW, kBotH, kBgPurple);

            src.DrawRect(0, 0, kBotW, 4, kHeaderPurple);

            DrawCenteredSysfont(src, "Vapecord ACHHD Plugin", 100, Color::White, kBotW);
            DrawCenteredSysfont(src, lang->get(TextID::SCAM_SUBTITLE), 122, kAccentLilac, kBotW);
        }

        void InitAntiScamScreen(void) {
            bool needsToUnpause = false;
            if (!Process::IsPaused()) {
                Process::Pause();
                needsToUnpause = true;
            }

            const Screen &top = OSD::GetTopScreen();
            const Screen &bot = OSD::GetBottomScreen();

            for (int i = 0; i < 2; ++i) {
                DrawTopScreen(top);
                DrawBottomScreen(bot);
                OSD::SwapBuffers();
            }

            bool pressed = false;
            while (!pressed) {
                Controller::Update();
                pressed = Controller::IsKeyPressed(Key::A);
                Sleep(Milliseconds(16));
            }

            do { 
                Controller::Update(); 
            } while (Controller::GetKeysDown() & Key::A);

            if (needsToUnpause) {
                Process::Play();
            }
        }
    }

    void ShowAntiScamScreen(void) {
        bool shown = false;
        Config::GetScamWarningShown(shown);

        if (shown) {
            return;
        }

        InitAntiScamScreen();
        Config::SetScamWarningShown(true);
    }
}

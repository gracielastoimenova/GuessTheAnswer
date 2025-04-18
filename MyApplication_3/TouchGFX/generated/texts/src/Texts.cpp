/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x50, 0x69, 0x63, 0x6b, 0x20, 0x61, 0x20, 0x63, 0x61, 0x74, 0x65, 0x67, 0x6f, 0x72, 0x79, 0x0, // @0 "Pick a category"
    0x47, 0x72, 0x6f, 0x75, 0x70, 0x20, 0x31, 0x20, 0x51, 0x75, 0x69, 0x7a, 0x21, 0x0, // @16 "Group 1 Quiz!"
    0x45, 0x6d, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64, 0x20, 0x73, 0x79, 0x73, 0x0, // @30 "Embedded sys"
    0x54, 0x6f, 0x70, 0x20, 0x73, 0x63, 0x6f, 0x72, 0x65, 0x73, 0x3a, 0x0, // @43 "Top scores:"
    0x41, 0x6c, 0x67, 0x6f, 0x72, 0x69, 0x74, 0x68, 0x6d, 0x73, 0x0, // @55 "Algorithms"
    0x47, 0x41, 0x4d, 0x45, 0x20, 0x4f, 0x56, 0x45, 0x52, 0x21, 0x0, // @66 "GAME OVER!"
    0x50, 0x6c, 0x61, 0x79, 0x20, 0x41, 0x67, 0x61, 0x69, 0x6e, 0x0, // @77 "Play Again"
    0x57, 0x65, 0x6c, 0x63, 0x6f, 0x6d, 0x65, 0x20, 0x74, 0x6f, 0x0, // @88 "Welcome to"
    0x44, 0x61, 0x74, 0x61, 0x62, 0x61, 0x73, 0x65, 0x73, 0x0, // @99 "Databases"
    0x56, 0x69, 0x65, 0x77, 0x20, 0x52, 0x61, 0x6e, 0x6b, 0x0, // @109 "View Rank"
    0x71, 0x75, 0x65, 0x73, 0x74, 0x69, 0x6f, 0x6e, 0x0, // @119 "question"
    0x2, 0x0, // @128 "<>"
    0x53, 0x63, 0x6f, 0x72, 0x65, 0x3a, 0x0, // @130 "Score:"
    0x70, 0x6f, 0x69, 0x6e, 0x74, 0x73, 0x0, // @137 "points"
    0x73, 0x75, 0x62, 0x6d, 0x69, 0x74, 0x0, // @144 "submit"
    0x53, 0x74, 0x61, 0x72, 0x74, 0x0, // @151 "Start"
    0x74, 0x68, 0x65, 0x0, // @157 "the"
    0x30, 0x30, 0x0, // @161 "00"
    0x31, 0x2e, 0x0, // @164 "1."
    0x31, 0x35, 0x0, // @167 "15"
    0x32, 0x2e, 0x0, // @170 "2."
    0x33, 0x2e, 0x0, // @173 "3."
    0x34, 0x2e, 0x0, // @176 "4."
    0x35, 0x2e, 0x0, // @179 "5."
    0x36, 0x2e, 0x0, // @182 "6."
    0x41, 0x49, 0x0, // @185 "AI"
    0x61, 0x31, 0x0, // @188 "a1"
    0x61, 0x32, 0x0, // @191 "a2"
    0x61, 0x33, 0x0, // @194 "a3"
    0x61, 0x34, 0x0, // @197 "a4"
    0x73, 0x31, 0x0, // @200 "s1"
    0x73, 0x32, 0x0, // @203 "s2"
    0x73, 0x33, 0x0, // @206 "s3"
    0x73, 0x34, 0x0, // @209 "s4"
    0x73, 0x35, 0x0, // @212 "s5"
    0x73, 0x36, 0x0 // @215 "s6"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const uint32_t indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}

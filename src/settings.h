#pragma once

#include <map>
#include <list>
#include <string>

#include "value.h"

namespace Settings {

class SettingsEntry
{
private:
    std::string _category;
    std::string _name;
    Value _value;
    Value _range;
    Value _default;

public:
    const std::string & category() const;
    const std::string & name() const;

    virtual const Value & defaultValue() const;
    virtual const Value & range() const;
    virtual bool is_default() const;

protected:
    SettingsEntry(const std::string category, const std::string name, const Value range, const Value def);
    virtual ~SettingsEntry();

    friend class Settings;
};

class Settings
{
public:
    static SettingsEntry indentationWidth;
    static SettingsEntry tabWidth;
    static SettingsEntry lineWrap;
    static SettingsEntry lineWrapIndentationStyle;
    static SettingsEntry lineWrapIndentation;
    static SettingsEntry lineWrapVisualizationBegin;
    static SettingsEntry lineWrapVisualizationEnd;
    static SettingsEntry showWhitespace;
    static SettingsEntry showWhitespaceSize;
    static SettingsEntry autoIndent;
    static SettingsEntry indentStyle;
    static SettingsEntry tabKeyFunction;
    static SettingsEntry highlightCurrentLine;
    static SettingsEntry enableBraceMatching;

    static Settings *inst(bool erase = false);

    void visit(class Visitor& visitor);

    Value defaultValue(const SettingsEntry& entry);
    Value get(const SettingsEntry& entry);
    void set(SettingsEntry& entry, const Value val);

private:
    Settings();
    virtual ~Settings();
};

class Visitor
{
public:
    Visitor();
    virtual ~Visitor();

    virtual void handle(SettingsEntry& entry) const = 0;
};

}
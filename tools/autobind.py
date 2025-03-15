import re
import os
import sys
from enum import Enum

class OutputType(Enum):
    NONE = 0
    LUA = 1
    CPP = 2

def write_lua_header():
    print("""
Game = {}
Assets = {}
UIWidgets = {}
Events = {}
---@alias ListenerID number
---@class Asset
local Asset = {}

--- Registers an asset.
function Asset:Register() end

--- Loads an 8-bit asset.
---@return integer
function Asset:Load8() end

--- Loads a 16-bit asset.
---@return integer
function Asset:Load16() end

--- Loads a 32-bit asset.
---@return integer
function Asset:Load32() end

--- Loads a Vtx asset.
---@return Vtx
function Asset:LoadVtx() end

--- Loads a Gfx asset.
---@return Gfx
function Asset:LoadGfx() end

--- Converts Asset to string.
---@return string
function Asset:__tostring() end

--- Registers an event listener.
---@param eventId EventID
---@param callback fun(event: EventID)
---@param priority EventPriority
---@return ListenerID
function RegisterListener(eventId, callback, priority) end

---@class Gfx
local Gfx = {}

--- Returns the next master display list.
---@return Gfx
function gNextMasterDisp() end

--- Returns a reference to the master display list.
---@return Gfx
function gRefMasterDisp() end

---@class Matrix
local Matrix = {}

--- Returns a reference to the GFX matrix.
---@return Matrix
function gRefGfxMatrix() end

--- Sets the primitive color.
---@param m number
---@param l number
---@param r number
---@param g number
---@param b number
---@param a number
function gDPSetPrimColor(m, l, r, g, b, a) end
""")

export_type = OutputType.NONE
event_list = []

def sanitize_type(member_type):
    global export_type
    member_type = member_type.strip()

    if export_type == OutputType.CPP:
        return member_type

    if len(member_type) == 0:
        return 'any'

    member_type = member_type.replace('uint8_t', 'number')
    member_type = member_type.replace('uint16_t', 'number')
    member_type = member_type.replace('uint32_t', 'number')
    member_type = member_type.replace('uint64_t', 'number')
    member_type = member_type.replace('int8_t', 'number')
    member_type = member_type.replace('int16_t', 'number')
    member_type = member_type.replace('int32_t', 'number')
    member_type = member_type.replace('int64_t', 'number')
    member_type = member_type.replace('size_t', 'number')
    member_type = member_type.replace('uintptr_t', 'number')
    member_type = member_type.replace('...', 'string')
    member_type = member_type.replace('*', '')
    member_type = member_type.replace('&', '')
    member_type = member_type.replace('const', '')
    member_type = member_type.replace('bool', 'boolean')
    member_type = member_type.replace('int', 'number')
    member_type = member_type.replace('float', 'number')
    member_type = member_type.replace('char', 'string')
    member_type = member_type.replace('unsigned', 'number')
    member_type = member_type.replace('u8', 'number')
    member_type = member_type.replace('u16', 'number')
    member_type = member_type.replace('u32', 'number')
    member_type = member_type.replace('u64', 'number')
    member_type = member_type.replace('s8', 'number')
    member_type = member_type.replace('s16', 'number')
    member_type = member_type.replace('s32', 'number')
    member_type = member_type.replace('s64', 'number')
    member_type = member_type.replace('void', 'nil')
    member_type = member_type.replace('f32', 'number')
    member_type = member_type.replace('f64', 'number')
    member_type = member_type.replace('double', 'number')
    member_type = member_type.replace('CONTROLLERBUTTONS_T', 'number')

    return member_type

blacklist = [
    'audio',
    'portable-file-dialogs.h',
    'rmonint.h',
    'PR/',
    'libultra/',
    'libc/',
    'dbgproto',
    'prevent',
    'piint',
    'siint',
    'sf64dma',
    'osint',
    'FrameInterpolation',
    'mods.h'
]

def parse_enums(header, as_value=False):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for enums node in config")

    # Regex pattern to match enum declarations
    enum_regex = re.compile(r"enum\s+(\w+)\s*(?:\s*:\s*(\w+))?[\s\n\r]*\{")

    in_enum = False
    enum_index = None
    enum_name = ""
    enum = {}

    global export_type

    for line in lines:
        line = line.strip()

        if not in_enum:
            # Check if the line matches the enum declaration pattern
            match = enum_regex.search(line)
            if match and len(match.groups()) > 1:
                enum_name = match.group(1)
                enum[enum_name] = []
                in_enum = True
                enum_index = -1
            continue

        if '}' in line:
            in_enum = False
            continue

        # Remove any comments and non-alphanumeric characters
        line = re.sub(r'(/\*.*?\*/)|(//.*$)|([^a-zA-Z0-9=_\-\.])', '', line)

        if len(line) == 0:
            continue

        if '=' in line:
            # Extract the value after the '=' sign
            value = line.split('=')[1].strip()
            # Extract the name before the '=' sign
            name = line.split('=')[0].strip()
            enum_index = int(value, 0)  # Convert the value to an integer with base 0 (detects hex, oct, etc.)
            enum[enum_name].append({
                'name': name,
                'value': enum_index
            })
        else:
            # Increment the enum index if no '=' is found
            enum_index += 1
            enum[enum_name].append({
                'name': line,
                'value': enum_index
            })

    for enum_name, values in enum.items():
        if export_type == OutputType.CPP:
            print(f'auto enum_{enum_name} = lua["{enum_name}"].force();')
            for i, entry in enumerate(values):
                key = entry['name']
                value = entry['value']
                if 'ifdef' in key or 'endif' in entry['name'] or 'else' in key:
                    continue
                key_name = key
                key_name = key_name.replace('EVENT_PRIORITY_', '')
                key_name = key_name.replace('SF64_VER_', '')
                print(f'enum_{enum_name}["{key_name}"] = (uint32_t) {value if as_value else key};')
            print('')
        elif export_type == OutputType.LUA:
            print(f'---@enum {enum_name}')
            print(f'{enum_name} = {{')
            for i, entry in enumerate(values):
                key = entry['name']
                value = entry['value']
                if 'ifdef' in key or 'endif' in entry['name'] or 'else' in key:
                    continue
                key_name = key
                key_name = key_name.replace('EVENT_PRIORITY_', '')
                key_name = key_name.replace('SF64_VER_', '')
                print(f'    {key_name} = {value}{"," if i < len(values) - 1 else ""}')
            print('}')
            print('')

def parse_structs(header):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for structs node in config")

    struct_regex = re.compile(r"struct\s+(\w+)\s*(?:\s*:\s*(\w+))?[\s\n\r]*\{")

    in_struct = False
    struct_name = ""
    found_union = False
    struct = {}

    global export_type

    for line in lines:
        line = line.strip()

        if not in_struct:
            match = struct_regex.search(line)
            if match and len(match.groups()) > 1:
                struct_name = match.group(1)
                struct[struct_name] = []
                in_struct = True
            continue

        if 'union' in line:
            found_union = True
            continue

        if '}' in line and not '{' in line and not found_union:
            in_struct = False
            continue

        if '}' in line and found_union:
            found_union = False
            continue

        line = re.sub(r'(/\*.*?\*/)', '', line)

        if ';' in line:
            if ':' in line and not 'sol:not_global' in line and not '::' in line:
                line = line.replace(' : ', ':')
                bitfield = line.split(':')[1].split(';')[0].strip()
                size = int(bitfield)
                struct[struct_name].append({
                    'name': line.split(':')[0].split(' ')[-1],
                    'export': 'bitfield',
                    'type': sanitize_type('u8' if size < 8 else 'u16' if size < 16 else 'u32' if size < 32 else 'u64')
                })
            elif '(' in line:
                struct[struct_name].append({
                    'name': f'{line.split('(')[0].split(' ')[-1]}',
                    'export': 'function',
                    'type': sanitize_type(line.split('(')[0].split(' ')[-2])
                })
            elif '[' in line:
                if len(line.split('[')) > 2:
                    continue
                struct[struct_name].append({
                    'name': line.split('[')[0].split(' ')[-1],
                    'export': 'variable',
                    'type': sanitize_type(line.split('[')[0].split(' ')[-2])
                })
            else:
                struct[struct_name].append({
                    'name': line.split(';')[0].split(' ')[-1],
                    'export': 'variable',
                    'type': sanitize_type(line.split(';')[0].split(' ')[-2])
                })

    for struct_name, members in struct.items():
        if len(members) == 0:
            continue
        
        if export_type == OutputType.CPP:
            print(f'lua.new_usertype<{struct_name}>("{struct_name}",')
            for i, member in enumerate(members):
                key = member['name'].replace('*', '')
                export = member['export']
                type = member['type']
                if export == 'bitfield':
                    print(f'    "{key}", sol::property([] ({struct_name}& self) -> {type} {{ return self.{key}; }}, [] ({struct_name}& self, {type} value) {{ self.{key} = value; }}){"," if i < len(members) - 1 else ""}')
                elif export == 'function':
                    print(f'    "{key}", &{struct_name}::{key}{"," if i < len(members) - 1 else ""}')
                else:
                    print(f'    "{key}", sol::property(&{struct_name}::{key}, &{struct_name}::{key}){"," if i < len(members) - 1 else ""}')
            print(');')
            print('')
        elif export_type == OutputType.LUA:
            print(f'---@class {struct_name}')
            print(f'{struct_name} = {{}}')
            for i, member in enumerate(members):
                key = member['name'].replace('*', '')
                export = member['export']
                type = member['type']
                if export == 'bitfield':
                    print(f'---@return {type}')
                    print(f'function {struct_name}:{key}() end')
                    print(f'---@param value {type}')
                    print(f'---@return {type}')
                    print(f'function {struct_name}:{key}(value) end')
                elif export == 'function':
                    print(f'---@return {type}')
                    print(f'function {struct_name}:{key}() end')
                else:
                    print(f'---@field {key} {type}')
            print('')

def parse_events(header):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for events node in config")

    in_event = False
    event_name = ""
    event = {}

    global export_type

    for line in lines:
        line = line.strip()
        if not in_event:
            if 'DEFINE_EVENT' in line:
                if ');' in line:
                    event_name = line.split('DEFINE_EVENT(')[1].split(')')[0].strip()
                    event[event_name] = ['event']
                    continue
                event_name = line.split('DEFINE_EVENT(')[1].split(',')[0].strip()
                event[event_name] = ['event']
                in_event = True
            continue

        if ');' in line:
            in_event = False
            continue

        if len(line) == 0:
            continue

        if ';' in line:
            member_name = line.split(';')[0].split(' ')[-1]
            event[event_name].append(member_name)
    
    for event_name, members in event.items():
        print(f'lua.new_usertype<{event_name}>("{event_name}",')
        for i, key in enumerate(members):
            key = key.replace('*', '')
            print(f'    "{key}", sol::property(&{event_name}::{key}, &{event_name}::{key}){"," if i < len(members) - 1 else ""}')
        print(');')
        print('')

def parse_externs(header, namespace=None):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for events node in config")

    global export_type

    for line in lines:
        line = re.sub(r'\s+', ' ', line.strip())
        if line.startswith('extern') and not 'void*' in line and not '"C"' in line or ('(' in line and ';' in line):
            if not '(' in line and not '[' in line:
                var_type = line.split(' ')[1]
                var_name = line.split(' ')[2].split(';')[0]
                if export_type == OutputType.CPP:
                    print(f'lua["Game"]["{var_name}"] = sol::overload([]() -> {var_type} {{ return {var_name}; }}, []({var_type} value) {{ {var_name} = value; }});')
                elif export_type == OutputType.LUA:
                    print(f'---@return {sanitize_type(var_type)}')
                    print(f'function Game.{var_name}() end')
                    print(f'---@param value {sanitize_type(var_type)}')
                    print(f'function Game.{var_name}(value) end')
            elif '[' in line and not '(' in line:
                dimension_len = len(line.split('[')) - 1
                var_name = line.split('[')[0].split(' ')[-1]
                var_type = line.split(' ')[1]
                is_pointer = True #'*' in line
                if export_type == OutputType.CPP:
                    if dimension_len == 1:
                        print(f'lua["Game"]["{var_name}"] = sol::overload([](int index) -> {var_type}{'' if is_pointer else '*'} {{ return {'' if is_pointer else '&'}{var_name}[index]; }}, [](int index, {var_type} value) {{ {var_name}[index] = value; }});')
                    elif dimension_len == 2:
                        print(f'lua["Game"]["{var_name}"] = sol::overload([](int index1, int index2) -> {var_type}{'' if is_pointer else '*'} {{ return {'' if is_pointer else '&'}{var_name}[index1][index2]; }}, [](int index1, int index2, {var_type} value) {{ {var_name}[index1][index2] = value; }});')
                    elif dimension_len == 3:
                        print('Unsupported 3D array')
                        exit()
                elif export_type == OutputType.LUA:
                    print(f'---@param index number')
                    print(f'---@return {sanitize_type(var_type)}[{dimension_len}]')
                    print(f'function Game.{var_name}(index) end')
                    print(f'---@param index number')
                    print(f'---@param value {sanitize_type(var_type)}')
                    print(f'function Game.{var_name}(index, value) end')
            elif '(' in line:
                if 'ALIGN_ASSET' in line:
                    var_name = line.split('[')[0].split(' ')[-1]
                    value = line.split('=')[-1].split(';')[0]
                    if export_type == OutputType.CPP:
                        print(f'lua["Assets"]["{var_name}"] = Asset{{ {var_name} }};')
                    elif export_type == OutputType.LUA:
                        print('---@type Asset')
                        print(f'Assets.{var_name} = {value.strip()}')
                    continue
                if 'define' in line or '\\' in line or 'typedef' in line or '[' in line or 'OSMesg' in line or 'Framebuffer' in line or 'TimerAction' in line or 'TimerTask' in line:
                    continue
                if '_DEG' in line or 'Fault' in line or 'sol:ignore' in line or 'sol:not_global' in line or '<T>' in line:
                    continue
                func_name = line.split('(')[0].split(' ')[-1]

                if len(func_name) == 0:
                    continue
                if 'CVarExists' in func_name or 'ResourceLoad' in func_name or 'void*' in func_name or 'ResourceClearCache' in func_name: # Report this to LUS
                    continue

                if export_type == OutputType.CPP:
                    if namespace:
                        print(f'lua["{namespace}"]["{func_name}"] = {namespace}::{func_name};')
                    else:
                        print(f'lua.set_function("{func_name}", {func_name});')
                elif export_type == OutputType.LUA:
                    return_type = line.split(' ')[0]
                    args = line.split('(')[1].split(')')[0].strip().split(',')
                    for i, arg in enumerate(args):
                        arg = arg.replace('const ', '')
                        arg = arg.replace(' *', '* ')
                        arg = arg.replace('...', 'varargs')
                        if len(arg.split(' ')) > 2:
                            if '=' in arg:
                                arg = arg.split('=')[0]
                                name = arg.split(' ')[2]
                                type = arg.split(' ')[1]
                            else:
                                name = arg.split(' ')[-1]
                                type = arg.split(' ')[-2]
                        else:
                            name = '_'+arg.split(' ')[-1]
                            type = arg.split(' ')[0]

                        name = name.replace('*', '')
                        name = name.replace('end', '_end')
                        if(len(name) == 0):
                            name = f'arg{i}'
                        args[i] = { 'name': name, 'type': type }

                    for i, arg in enumerate(args):
                        print(f'---@param {arg["name"]} {sanitize_type(arg["type"])}')

                    print(f'---@return {sanitize_type(return_type)}')
                    if namespace:
                        print(f'function {namespace}.{func_name}({', '.join([f'{arg["name"]}' for arg in args])}) end')
                    else:
                        print(f'function {func_name}({', '.join([f'{arg["name"]}' for arg in args])}) end')

def is_blacklisted(file):
    for item in blacklist:
        if item in file:
            return True
    return False

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python autobind.py <output_type>")
        exit()

    export_type = OutputType.LUA if sys.argv[1] == 'lua' else OutputType.CPP

    if export_type == OutputType.LUA:
        write_lua_header()

    for root, dirs, files in os.walk("include"):
        for file in files:
            # Join root and file to get full path
            file_path = os.path.join(root, file)
            # Check if the file is blacklisted
            if(is_blacklisted(file_path)):
                continue

            parse_enums(file_path, True if 'scripting.h' in file_path else False)
            parse_structs(file_path)
            parse_externs(file_path)
    
    parse_enums("src/port/hooks/impl/EventSystem.h")
    parse_structs("src/port/hooks/impl/EventSystem.h")
    parse_externs("libultraship/src/public/bridge/consolevariablebridge.h")

    parse_enums("src/port/Engine.h")
    parse_externs("src/port/Engine.h")
    parse_externs("src/port/ui/UIWidgets.h", 'UIWidgets')
    parse_externs("libultraship/src/public/bridge/resourcebridge.h")

    for root, dirs, files in os.walk("src/port/hooks/list"):
        for file in files:
            parse_events(os.path.join(root, file))

    if export_type == OutputType.LUA:
        print('---@enum EventID')
        print('EventID = {')
        for event_name in event_list:
            print(f'    {event_name} = -1' + (',' if event_name != event_list[-1] else ''))
        print('}')

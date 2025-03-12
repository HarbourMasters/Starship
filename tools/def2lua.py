import re
import os

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

event_list = []

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

def sanitize_type(member_type):
    member_type = member_type.strip()
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

        if '}' in line and not found_union:
            in_struct = False
            continue
            
        if '}' in line and found_union:
            found_union = False
            continue

        line = re.sub(r'(/\*.*?\*/)', '', line)

        if ';' in line and not ':' in line:
            # if ':' in line:
            #     member_name = line.split(' ')[-3].split(':')[0]
            #     continue
            if '[' in line:
                if len(line.split('[')) > 2:
                    continue
                member_name = line.split('[')[0].split(' ')[-1]
                member_type = line.split(' ')[-2]
            else:
                member_name = line.split(';')[0].split(' ')[-1]
                member_type = line.split(';')[0].split(' ')[-2]

            
            struct[struct_name].append(member_name + ' ' + sanitize_type(member_type))

    for struct_name, members in struct.items():
        if len(members) == 0:
            continue
        # TODO: Add support for functions
        print(f'---@class {struct_name}')
        for i, key in enumerate(members):
            key = key.replace('*', '')
            print(f'---@field {key}')
        print(f'{struct_name} = {{}}')
        if struct_name == 'Object':
            print(f'---@return Actor')
            print(f'function {struct_name}:asActor() end')
            print(f'---@return Boss')
            print(f'function {struct_name}:asBoss() end')
            print(f'---@return Scenery')
            print(f'function {struct_name}:asScenery() end')
            print(f'---@return Scenery360')
            print(f'function {struct_name}:asScenery360() end')
            print(f'---@return Sprite')
            print(f'function {struct_name}:asSprite() end')
            print(f'---@return Item')
            print(f'function {struct_name}:asItem() end')
            print(f'---@return Effect')
            print(f'function {struct_name}:asEffect() end')
            print(f'---@return {struct_name}')
            print(f'function {struct_name}:asRef() end')
        elif struct_name == 'Object' or struct_name == 'ObjectInfo' or struct_name == 'Actor' or struct_name == 'Boss' or struct_name == 'Scenery' or struct_name == 'Scenery360' or struct_name == 'Sprite' or struct_name == 'Item' or struct_name == 'Effect':
            print(f'---@return {struct_name}')
            print(f'function {struct_name}:asRef() end')
        elif struct_name.startswith('Vec') or struct_name.startswith('Plane') or struct_name == 'PosRot' or struct_name == 'CameraPoint' or struct_name == 'Triangle':
            print(f'---@return {struct_name}')
            print(f'function {struct_name}:asRef() end')
            if struct_name.startswith('Vec'):
                print(f'---@return f32')
                print(f'function {struct_name}:xRef() end')
                print(f'---@return f32')
                print(f'function {struct_name}:yRef() end')
                print(f'---@return f32')
                print(f'function {struct_name}:zRef() end')
        print('')

def parse_events(header):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for events node in config")

    global event_list
    in_event = False
    event_name = ""
    event = {}

    for line in lines:
        line = line.strip()
        if not in_event:
            if 'DEFINE_EVENT' in line:
                if ');' in line:
                    event_name = line.split('DEFINE_EVENT(')[1].split(')')[0].strip()
                    event[event_name] = ['event IEvent']
                    continue
                event_name = line.split('DEFINE_EVENT(')[1].split(',')[0].strip()
                event[event_name] = ['event IEvent']
                in_event = True
            continue

        if ');' in line:
            in_event = False
            continue

        if len(line) == 0:
            continue

        if ';' in line:
            member_name = line.split(';')[0].split(' ')[-1]
            member_type = line.split(';')[0].split(' ')[-2]
            event[event_name].append(member_name + ' ' + sanitize_type(member_type))
    
    for event_name, members in event.items():
        print(f'---@class {event_name}')
        event_list.append(event_name)
        for i, key in enumerate(members):
            key = key.replace('*', '')
            print(f'---@field {key}')
        print('')
    print('')

def parse_externs(header, namespace=None):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for events node in config")

    for line in lines:
        line = re.sub(r'\s+', ' ', line.strip())
        if line.startswith('extern') and not 'void*' in line and not '"C"' in line or ('(' in line and ';' in line):
            if not '(' in line and not '[' in line:
                var_type = line.split(' ')[1]
                var_name = line.split(' ')[2].split(';')[0]
                print(f'---@return {sanitize_type(var_type)}')
                print(f'function Game.{var_name}() end')
            elif '[' in line and not '(' in line:
                dimension_len = len(line.split('[')) - 1
                var_name = line.split('[')[0].split(' ')[-1]
                var_type = line.split(' ')[1]
                print(f'---@return {sanitize_type(var_type)}[{dimension_len}]')
                print(f'function Game.{var_name}() end')
            elif '(' in line:
                if 'ALIGN_ASSET' in line:
                    var_name = line.split('[')[0].split(' ')[-1]
                    value = line.split('=')[-1].split(';')[0]
                    print('---@type Asset')
                    print(f'Assets.{var_name} = {value.strip()}')
                    continue
                if 'define' in line or '\\' in line or 'typedef' in line or '[' in line or 'OSMesg' in line or 'Framebuffer' in line or 'TimerAction' in line or 'TimerTask' in line:
                    continue
                if '_DEG' in line or 'Fault' in line or 'sol:ignore' in line or '<T>' in line or '<' in line:
                    continue
                func_name = line.split('(')[0].split(' ')[-1]
                if len(func_name) == 0:
                    continue
                if 'CVarExists' in func_name or 'ResourceLoad' in func_name or 'void*' in func_name or 'ResourceClearCache' in func_name: # Report this to LUS
                    continue
                
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
    print("Game = {}")
    print("Assets = {}")
    print("UIWidgets = {}")
    header = """
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
"""
    print(header)
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

    print('---@enum EventID')
    print('EventID = {')
    for event_name in event_list:
        print(f'    {event_name} = -1' + (',' if event_name != event_list[-1] else ''))
    print('}')
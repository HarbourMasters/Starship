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
        print(f'auto enum_{enum_name} = lua["{enum_name}"].force();')
        for i, entry in enumerate(values):
            key = entry['name']
            value = entry['value']
            if 'ifdef' in key or 'endif' in entry['name'] or 'else' in key:
                continue
            print(f'enum_{enum_name}["{key.replace('EVENT_PRIORITY_', '')}"] = (uint32_t) {value if as_value else key};')
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
            else:
                member_name = line.split(';')[0].split(' ')[-1]
            struct[struct_name].append(member_name)

    for struct_name, members in struct.items():
        if len(members) == 0:
            continue
        print(f'lua.new_usertype<{struct_name}>("{struct_name}",')
        for i, key in enumerate(members):
            key = key.replace('*', '')
            print(f'    "{key}", sol::property(&{struct_name}::{key}, &{struct_name}::{key}){"," if i < len(members) - 1 else ""}')
        if struct_name == 'Object':
            print(f'   ,"asActor", &{struct_name}::asActor,')
            print(f'    "asBoss", &{struct_name}::asBoss,')
            print(f'    "asScenery", &{struct_name}::asScenery,')
            print(f'    "asScenery360", &{struct_name}::asScenery360,')
            print(f'    "asSprite", &{struct_name}::asSprite,')
            print(f'    "asItem", &{struct_name}::asItem,')
            print(f'    "asEffect", &{struct_name}::asEffect')
        print(');')
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
        # print(f'lua["{event_name}ID"] = {event_name}ID;')
        print(f'lua.new_usertype<{event_name}>("{event_name}",')
        for i, key in enumerate(members):
            key = key.replace('*', '')
            print(f'    "{key}", sol::property(&{event_name}::{key}, &{event_name}::{key}){"," if i < len(members) - 1 else ""}')
        print(');')
        print('')

def parse_externs(header):
    try:
        with open(header, 'r') as file:
            lines = file.readlines()
    except IOError:
        raise RuntimeError("Failed to open header files for events node in config")

    for line in lines:
        line = re.sub(r'\s+', ' ', line.strip())
        if line.startswith('extern') and not '"C"' in line or ('(' in line and ';' in line):
            if not '(' in line and not '[' in line:
                var_type = line.split(' ')[1]
                var_name = line.split(' ')[2].split(';')[0]
                # if '*' in line:
                #     print(f'lua["Game"]["{var_name}"] = {var_name};')
                # else:
                #     print(f'lua["Game"]["{var_name}"] = &{var_name};')
                print(f'lua["Game"]["{var_name}"] = sol::overload([]() -> {var_type} {{ return {var_name}; }}, []({var_type} value) {{ {var_name} = value; }});')

                # print(f'context["{var_name}"] = sol::property([]() -> {var_type} {{ return {var_name}; }}, []({var_type} value) {{ {var_name} = value; }});')
                # print(f'lua["{var_name}"] = sol::var(std::ref({var_name}));')
                # print(f'lua["{var_name}"] = sol::as_pointer({var_name});')
                # print(f'lua.set("{var_name}", sol::var({var_name}));')
            elif '[' in line and not '(' in line:
                dimension_len = len(line.split('[')) - 1
                var_name = line.split('[')[0].split(' ')[-1]
                var_type = line.split(' ')[1]
                is_pointer = '*' in line
                if dimension_len == 1:
                    print(f'lua["Game"]["{var_name}"] = sol::overload([](int index) -> {var_type}{'' if is_pointer else '*'} {{ return {'' if is_pointer else '&'}{var_name}[index]; }}, [](int index, {var_type} value) {{ {var_name}[index] = value; }});')
                elif dimension_len == 2:
                    print(f'lua["Game"]["{var_name}"] = sol::overload([](int index1, int index2) -> {var_type}{'' if is_pointer else '*'} {{ return {'' if is_pointer else '&'}{var_name}[index1][index2]; }}, [](int index1, int index2, {var_type} value) {{ {var_name}[index1][index2] = value; }});')
                elif dimension_len == 3:
                    print('Unsupported 3D array')
                    exit()
            elif '(' in line:
                if 'ALIGN_ASSET' in line:
                    var_name = line.split('[')[0].split(' ')[-1]
                    # print(f'lua["Assets"]["{var_name}"] = {var_name};')
                    print(f'lua["Assets"]["{var_name}"] = Asset{{ {var_name} }};')
                    continue
                if 'define' in line or '\\' in line or 'typedef' in line or '[' in line or 'OSMesg' in line or 'Framebuffer' in line or 'TimerAction' in line or 'TimerTask' in line:
                    continue
                if '_DEG' in line or 'Fault' in line:
                    continue
                func_name = line.split('(')[0].split(' ')[-1]
                # print('Function:', func_name)
                if len(func_name) == 0:
                    continue
                if 'CVarExists' in func_name: # Report this to LUS
                    continue
                print(f'lua.set_function("{func_name}", {func_name});')

def is_blacklisted(file):
    for item in blacklist:
        if item in file:
            return True
    return False

if __name__ == "__main__":
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

    for root, dirs, files in os.walk("src/port/hooks/list"):
        for file in files:
            parse_events(os.path.join(root, file))


import sys
import os
import re
import argparse

def amalgamate(file_path, include_dirs, processed, out_file):
    abs_path = os.path.abspath(file_path)
    
    # Inclusion guard prevents infinite loops within a single .c file's tree
    if abs_path in processed:
        return
    processed.add(abs_path)

    try:
        with open(abs_path, 'r', encoding='utf-8') as f:
            for line in f:
                match = re.match(r'^\s*#\s*include\s+([<"])([^>"]+)[>"]', line)
                if match:
                    delimiter = match.group(1)
                    header_name = match.group(2)
                    header_path = None
                    
                    search_paths = list(include_dirs)
                    if delimiter == '"':
                        local_dir = os.path.dirname(abs_path)
                        search_paths.insert(0, local_dir)
                    
                    for path in search_paths:
                        potential_path = os.path.join(path, header_name)
                        if os.path.exists(potential_path):
                            header_path = potential_path
                            break
                    
                    if header_path:
                        out_file.write(f"/* --- Start: {header_name} --- */\n")
                        amalgamate(header_path, include_dirs, processed, out_file)
                        out_file.write(f"/* --- End: {header_name} --- */\n")
                    else:
                        out_file.write(line) 
                else:
                    out_file.write(line)
    except Exception as e:
        print(f"Warning: Could not process {abs_path}: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Inject local headers into a single C file.")
    parser.add_argument('--out', required=True, help="The output .c file")
    parser.add_argument('--includes', nargs='*', default=[], help="Include directories")
    
    # Changed from --srcs (list) to --src (single file)
    parser.add_argument('--src', required=True, help="Input .c file")
    
    args = parser.parse_args()

    # The processed set is only maintained for this specific .c file
    local_processed = set()
    
    with open(args.out, 'w', encoding='utf-8') as out_file:
        out_file.write(f"/* === Processed Source: {os.path.basename(args.src)} === */\n\n")
        amalgamate(args.src, args.includes, local_processed, out_file)
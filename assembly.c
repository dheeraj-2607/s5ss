#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LABEL_LENGTH 50
#define MAX_OPERAND_LENGTH 50
#define MAX_LINES 1000
#define SYMBOL_TABLE_SIZE 100
#define MAX_RECORD_LENGTH 80

// Structure for symbol table
typedef struct {
    char label[MAX_LABEL_LENGTH];
    int address;
} SymbolEntry;

// Structure for each line of code
typedef struct {
    char original_line[256];
    char label[MAX_LABEL_LENGTH];
    char opcode[MAX_OPERAND_LENGTH];
    char operand1[MAX_OPERAND_LENGTH];
    char operand2[MAX_OPERAND_LENGTH];
    int address;
    int line_number;
    int has_label;
} CodeLine;

// Structure for text record
typedef struct {
    int start_address;
    int length;
    char data[MAX_RECORD_LENGTH];
} TextRecord;

// Global variables
SymbolEntry symbol_table[SYMBOL_TABLE_SIZE];
int symbol_count = 0;
CodeLine source_code[MAX_LINES];
int line_count = 0;
int current_address = 0;
int program_start = 0;
int program_length = 0;
char program_name[20];

// Function prototypes
void pass1(FILE *input_file);
void pass2(FILE *output_file);
void add_to_symbol_table(char *label, int address);
int find_symbol_address(char *label);
void parse_line(char *line, char *label, char *opcode, char *operand1, char *operand2, int *has_label);
int is_directive(char *opcode);
int get_opcode_value(char *opcode);
int is_blank_line(char *line);
void write_header_record(FILE *output_file);
void write_text_records(FILE *output_file);
void write_end_record(FILE *output_file);
void init_text_record(TextRecord *record, int start_addr);
void add_to_text_record(TextRecord *record, int machine_code);
void write_current_text_record(FILE *output_file, TextRecord *record);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file.txt> <output_file.txt>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error: Cannot open input file %s\n", argv[1]);
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        printf("Error: Cannot create output file %s\n", argv[2]);
        fclose(input_file);
        return 1;
    }

    printf("Starting hand assembly process...\n");
    
    // Initialize program name from input filename
    strcpy(program_name, "PROGRAM");
    
    // Pass 1: Build symbol table and determine addresses
    printf("Pass 1: Building symbol table...\n");
    pass1(input_file);
    fclose(input_file);

    // Pass 2: Generate hand assembly with records
    printf("Pass 2: Generating hand assembly with records...\n");
    pass2(output_file);
    fclose(output_file);

    printf("Hand assembly completed successfully!\n");
    printf("Symbol table entries: %d\n", symbol_count);
    printf("Lines processed: %d\n", line_count);
    printf("Program length: %d bytes\n", program_length);

    return 0;
}

// Pass 1: Build symbol table and determine addresses
void pass1(FILE *input_file) {
    char line[256];
    int line_num = 0;
    int start_address_found = 0;

    current_address = 0;
    program_start = 0;

    while (fgets(line, sizeof(line), input_file)) {
        line_num++;
        
        // Store original line
        strcpy(source_code[line_count].original_line, line);
        source_code[line_count].line_number = line_num;
        
        // Skip empty lines but keep them for output
        if (is_blank_line(line)) {
            source_code[line_count].address = current_address;
            line_count++;
            continue;
        }
        
        // Initialize fields
        strcpy(source_code[line_count].label, "");
        strcpy(source_code[line_count].opcode, "");
        strcpy(source_code[line_count].operand1, "");
        strcpy(source_code[line_count].operand2, "");
        source_code[line_count].has_label = 0;

        // Parse the line
        parse_line(line, source_code[line_count].label, 
                  source_code[line_count].opcode, 
                  source_code[line_count].operand1, 
                  source_code[line_count].operand2,
                  &source_code[line_count].has_label);

        // Set address for this line
        source_code[line_count].address = current_address;

        // Add label to symbol table if present
        if (source_code[line_count].has_label) {
            add_to_symbol_table(source_code[line_count].label, current_address);
        }

        // Handle START directive
        if (strcmp(source_code[line_count].opcode, "START") == 0) {
            if (strlen(source_code[line_count].operand1) > 0) {
                program_start = atoi(source_code[line_count].operand1);
                current_address = program_start;
                source_code[line_count].address = current_address;
                start_address_found = 1;
            }
        }
        // Handle ORG directive
        else if (strcmp(source_code[line_count].opcode, "ORG") == 0) {
            if (strlen(source_code[line_count].operand1) > 0) {
                current_address = atoi(source_code[line_count].operand1);
            }
        }
        // Handle END directive - no address change
        else if (strcmp(source_code[line_count].opcode, "END") == 0) {
            // Do nothing for END directive
        }
        // Handle data allocation directives
        else if (is_directive(source_code[line_count].opcode)) {
            if (strcmp(source_code[line_count].opcode, "DB") == 0) {
                current_address += 1;
            } else if (strcmp(source_code[line_count].opcode, "DW") == 0) {
                current_address += 2;
            } else if (strcmp(source_code[line_count].opcode, "DS") == 0) {
                int size = atoi(source_code[line_count].operand1);
                if (size > 0) current_address += size;
                else current_address += 1;
            }
        }
        // Regular instruction
        else if (strlen(source_code[line_count].opcode) > 0) {
            current_address += 3; // Assume 3 bytes per instruction
        }

        line_count++;
        if (line_count >= MAX_LINES) break;
    }

    program_length = current_address - program_start;
}

// Pass 2: Generate hand assembly with proper records
void pass2(FILE *output_file) {
    fprintf(output_file, "HAND ASSEMBLY OUTPUT\n");
    fprintf(output_file, "====================\n\n");
    
    // Write object code records
    write_header_record(output_file);
    write_text_records(output_file);
    write_end_record(output_file);
    
    fprintf(output_file, "\n\nSOURCE CODE LISTING\n");
    fprintf(output_file, "===================\n");
    fprintf(output_file, "Addr    Line#  Source Code\n");
    fprintf(output_file, "-----   -----  ----------------------------------\n");
    
    for (int i = 0; i < line_count; i++) {
        if (is_blank_line(source_code[i].original_line)) {
            fprintf(output_file, "        %-6d%s", source_code[i].line_number, source_code[i].original_line);
        } else {
            fprintf(output_file, "%-6d  %-6d%s", source_code[i].address, source_code[i].line_number, source_code[i].original_line);
        }
    }
    
    fprintf(output_file, "\n\nSYMBOL TABLE\n");
    fprintf(output_file, "============\n");
    fprintf(output_file, "Label               Address\n");
    fprintf(output_file, "----------------    ------\n");
    
    for (int i = 0; i < symbol_count; i++) {
        fprintf(output_file, "%-20s %04X\n", symbol_table[i].label, symbol_table[i].address);
    }
}

// Write header record
void write_header_record(FILE *output_file) {
    fprintf(output_file, "OBJECT CODE RECORDS\n");
    fprintf(output_file, "===================\n\n");
    fprintf(output_file, "H%-6s%06X%06X\n", program_name, program_start, program_length);
}

// Write text records
void write_text_records(FILE *output_file) {
    TextRecord current_record;
    int record_started = 0;
    
    for (int i = 0; i < line_count; i++) {
        if (is_blank_line(source_code[i].original_line) || 
            strcmp(source_code[i].opcode, "END") == 0 ||
            strcmp(source_code[i].opcode, "START") == 0) {
            continue;
        }
        
        // Skip directives that don't generate code
        if (is_directive(source_code[i].opcode) && 
            strcmp(source_code[i].opcode, "ORG") != 0) {
            continue;
        }
        
        // Handle ORG directive - start new text record
        if (strcmp(source_code[i].opcode, "ORG") == 0) {
            if (record_started) {
                write_current_text_record(output_file, &current_record);
                record_started = 0;
            }
            continue;
        }
        
        // Generate machine code for instruction
        int machine_code = 0;
        if (strlen(source_code[i].opcode) > 0 && !is_directive(source_code[i].opcode)) {
            machine_code = get_opcode_value(source_code[i].opcode) << 16;
            
            // Handle operands
            if (strlen(source_code[i].operand1) > 0) {
                if (isdigit(source_code[i].operand1[0])) {
                    machine_code |= (atoi(source_code[i].operand1) & 0xFFFF);
                } else {
                    int addr = find_symbol_address(source_code[i].operand1);
                    if (addr >= 0) {
                        machine_code |= (addr & 0xFFFF);
                    }
                }
            }
            
            // Start new record if needed
            if (!record_started) {
                init_text_record(&current_record, source_code[i].address);
                record_started = 1;
            }
            
            // Add to current record
            add_to_text_record(&current_record, machine_code);
        }
    }
    
    // Write final text record
    if (record_started) {
        write_current_text_record(output_file, &current_record);
    }
}

// Write end record
void write_end_record(FILE *output_file) {
    fprintf(output_file, "E%06X\n", program_start);
}

// Initialize text record
void init_text_record(TextRecord *record, int start_addr) {
    record->start_address = start_addr;
    record->length = 0;
    memset(record->data, 0, sizeof(record->data));
}

// Add machine code to text record
void add_to_text_record(TextRecord *record, int machine_code) {
    if (record->length + 3 <= MAX_RECORD_LENGTH) {
        // Convert machine code to hex string (3 bytes)
        sprintf(record->data + record->length, "%06X", machine_code);
        record->length += 6; // 6 hex characters = 3 bytes
    }
}

// Write current text record to file
void write_current_text_record(FILE *output_file, TextRecord *record) {
    if (record->length > 0) {
        fprintf(output_file, "T%06X%02X%s\n", record->start_address, record->length/2, record->data);
    }
}

// Add symbol to symbol table
void add_to_symbol_table(char *label, int address) {
    if (symbol_count < SYMBOL_TABLE_SIZE) {
        // Check if symbol already exists
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i].label, label) == 0) {
                printf("Warning: Duplicate label '%s' at address %d\n", label, address);
                return;
            }
        }
        
        strcpy(symbol_table[symbol_count].label, label);
        symbol_table[symbol_count].address = address;
        symbol_count++;
    }
}

// Find symbol address in symbol table
int find_symbol_address(char *label) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].label, label) == 0) {
            return symbol_table[i].address;
        }
    }
    return -1;
}

// Parse a line into label, opcode, and operands
void parse_line(char *line, char *label, char *opcode, char *operand1, char *operand2, int *has_label) {
    char temp[256];
    strcpy(temp, line);
    
    // Remove newline character
    temp[strcspn(temp, "\n")] = 0;
    
    char *token = strtok(temp, " \t,");
    int part = 0;
    *has_label = 0;
    
    while (token != NULL) {
        switch (part) {
            case 0:
                // Check if it's a label (ends with colon) or opcode
                if (strchr(token, ':') != NULL) {
                    // It's a label
                    strcpy(label, token);
                    // Remove the colon
                    char *colon = strchr(label, ':');
                    if (colon != NULL) *colon = '\0';
                    *has_label = 1;
                } else {
                    // It's an opcode (no label on this line)
                    strcpy(opcode, token);
                }
                break;
            case 1:
                if (strlen(opcode) == 0) {
                    // Previous token was label, this is opcode
                    strcpy(opcode, token);
                } else {
                    // This is first operand
                    strcpy(operand1, token);
                }
                break;
            case 2:
                strcpy(operand2, token);
                break;
        }
        part++;
        token = strtok(NULL, " \t,");
    }
}

// Check if opcode is a directive
int is_directive(char *opcode) {
    if (strlen(opcode) == 0) return 0;
    
    char *directives[] = {"START", "END", "ORG", "DB", "DW", "DS", "EQU"};
    int num_directives = 7;
    
    for (int i = 0; i < num_directives; i++) {
        if (strcmp(opcode, directives[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Get numeric value for opcode (simplified)
int get_opcode_value(char *opcode) {
    // Simple mapping of opcodes to numeric values
    struct {
        char *opcode;
        int value;
    } opcode_map[] = {
        {"MOV", 0x01}, {"ADD", 0x02}, {"SUB", 0x03}, {"MUL", 0x04},
        {"DIV", 0x05}, {"JMP", 0x06}, {"JZ", 0x07}, {"JNZ", 0x08},
        {"CMP", 0x09}, {"LOAD", 0x0A}, {"STORE", 0x0B}, {"PUSH", 0x0C},
        {"POP", 0x0D}, {"CALL", 0x0E}, {"RET", 0x0F}, {"HLT", 0x10}
    };
    
    for (int i = 0; i < 16; i++) {
        if (strcmp(opcode, opcode_map[i].opcode) == 0) {
            return opcode_map[i].value;
        }
    }
    
    return 0; // Unknown opcode
}

// Check if line is blank (only whitespace)
int is_blank_line(char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return 0;
        }
        line++;
    }
    return 1;
}

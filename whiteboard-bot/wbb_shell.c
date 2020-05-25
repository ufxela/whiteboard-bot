
#include "wbb-extra.h"

// note: no command should be a prefix of another.
#define MAX_CMD_SIZE 64

// handlers return 1 if we should quit.
typedef int (*cmd_handler)(wbb_t * wbb, char * arg);

typedef struct {
    char name[MAX_CMD_SIZE];
    char example[MAX_CMD_SIZE];
    unsigned name_len;
    cmd_handler handler;
} wbb_cmd_t; 

static int goto_handler(wbb_t * wbb, char * arg);

static int quit_handler(wbb_t * wbb, char * arg);

static int lift_handler(wbb_t * wbb, char * arg);

static int place_handler(wbb_t * wbb, char * arg);

static int rel_goto_handler(wbb_t * wbb, char * arg);

static int arc_handler(wbb_t * wbb, char * arg);

static int circ_handler(wbb_t * wbb, char * arg);

static int let_handler(wbb_t * wbb, char * arg);

static int complete_handler(wbb_t * wbb, char * arg);

static int list_handler(wbb_t * wbb, char * arg);

static int accel_handler(wbb_t * wbb, char * arg);

static int server_handler(wbb_t * wbb, char * arg);

// perhaps add a go home command
// perhaps a stop command?
// perhaps a lift/place enqueue cmd which doesn't do an immediate lift/place but rather does a 
// enqueued one which is preformed in the enqueued pos relative to all of the stepper movements.
// allow user to set speed/font
static wbb_cmd_t commands[] = {
    { .name = "list", .example="list", .name_len = 4, .handler=list_handler },
    { .name = "accel", .example="accel [nsecs]", .name_len = 5, .handler=accel_handler },
    { .name = "lift", .example="lift", .name_len = 4, .handler=lift_handler },
    { .name = "place", .example="place", .name_len = 5, .handler=place_handler },
    { .name = "goto", .example="goto [x],[y]", .name_len = 4, .handler=goto_handler },
    { .name = "rel_goto", .example="rel_goto [x],[y]", .name_len = 8, .handler=rel_goto_handler },
    { .name = "arc", .example="arc [rad],[ppc],[sp],[ep]", .name_len = 3, .handler=arc_handler },
    { .name = "circ", .example="circ [rad],[ppc]", .name_len = 4, .handler=circ_handler },
    { .name = "let", .example="let [letters]", .name_len = 3, .handler=let_handler },
    { .name = "complete", .example="complete", .name_len = 8, .handler=complete_handler },
    { .name = "quit", .example="quit", .name_len = 4, .handler=quit_handler },
    { .name = "server", .example="server", .name_len = 6, .handler=server_handler },
    { 0 }
};

static void print_cmds(){
    output("---------------- commands ----------------\n");
    for(wbb_cmd_t * curr = commands; *((unsigned *) curr) != 0; curr++){
        output("command %s: example: \"%s\"\n", curr->name, curr->example);
    }
    output("------------------------------------------\n");
}

static int handler_wrapper(wbb_cmd_t * cmd, char * buf, wbb_t * wbb){
    char * arg = &buf[cmd->name_len];
    return cmd->handler(wbb, arg);
}

static int quit_handler(wbb_t * wbb, char * arg){
    output("WBB Shutting Down!\n");
    return 1;
}

static int goto_handler(wbb_t * wbb, char * arg){
    if(arg[0] != ' '){
        output("ERROR in command\n");
        return 0;
    }
    int x, y;
    char * comma_i = strchr(arg, ',');
    char x_str[MAX_CMD_SIZE];
    char y_str[MAX_CMD_SIZE];
    memcpy(x_str, arg + 1, comma_i - arg + 1); // skip the space in arg
    x_str[comma_i - arg - 1] = 0;
    x = atoi(x_str);
    y = atoi(comma_i + 1);
    output("Going to (%d,%d)\n", x, y);
    wbb_go_to_coords(wbb, x, y);
    return 0;
}

static int lift_handler(wbb_t * wbb, char * arg){
    wbb_lift_pen(wbb);
    return 0;
}

static int place_handler(wbb_t * wbb, char * arg){
    wbb_place_pen(wbb);
    return 0;
}

static int rel_goto_handler(wbb_t * wbb, char * arg){
    if(arg[0] != ' '){
        output("ERROR in command %s\n", arg);
        return 0;
    }
    int x, y;
    char * comma_i = strchr(arg, ',');
    char x_str[MAX_CMD_SIZE];
    char y_str[MAX_CMD_SIZE];
    memcpy(x_str, arg + 1, comma_i - arg + 1); // skip the space in arg
    x_str[comma_i - arg - 1] = 0;
    x = atoi(x_str); // bad... strtonum better
    y = atoi(comma_i + 1);
    output("Moving (%d,%d) relative\n", x, y);
    wbb_go_to_coords_relative(wbb, x, y);
    return 0;
}

static int arc_handler(wbb_t * wbb, char * arg){
    //[rad],[ppc],[sp],[ep]
    if(arg[0] != ' '){
        output("ERROR in command %s\n", arg);
        return 0;
    }
    int rad, ppc, sp, ep;

    char * comma_i = strchr(arg, ',');
    rad = atoi(arg);
    arg = comma_i + 1;
    comma_i = strchr(arg, ',');
    ppc = atoi(arg);
    arg = comma_i + 1;
    comma_i = strchr(arg, ',');
    sp = atoi(arg);
    arg = comma_i + 1;
    comma_i = strchr(arg, ',');
    ep = atoi(arg);

    if(rad <= 0 || ppc <= 0){
        output("ERROR in command %s\n", arg);
        return 0;
    }
    output("drawing arc with rad %d and npoints per circ. %d start pt %d and end pt%d\n", rad, ppc, sp, ep);    
    wbb_draw_arc(wbb, rad, ppc, sp, ep);
    return 0;
}

static int circ_handler(wbb_t * wbb, char * arg){
    if(arg[0] != ' '){
        output("ERROR in command %s\n", arg);
        return 0;
    }
    int rad, pts;
    char * comma_i = strchr(arg, ',');
    char rad_str[MAX_CMD_SIZE];
    char pts_str[MAX_CMD_SIZE];
    memcpy(rad_str, arg + 1, comma_i - arg + 1); // skip the space in arg
    rad_str[comma_i - arg - 1] = 0;
    rad = atoi(rad_str); // bad... strtonum better
    pts = atoi(comma_i + 1);
    if(rad <= 0 || pts <= 0){
        output("ERROR in command %s\n", arg);
        return 0;
    }
    output("drawing circle with rad %d and npoints %d\n", rad, pts);    
    wbb_draw_circle(wbb, rad, pts);
    return 0;
}

static int let_handler(wbb_t * wbb, char * arg){
    char * letters = arg + 1; // skip the space
    printk("wbb drawing letters %s\n", letters);
    wbb_draw_letters(wbb, letters);
    return 0;
}

static int complete_handler(wbb_t * wbb, char * arg){
    wbb_complete(wbb);
    return 0;
}

static int list_handler(wbb_t * wbb, char * arg){
    print_cmds();
    return 0;
}

static int accel_handler(wbb_t * wbb, char * arg){
    int nsecs = atoi(arg);
    if(nsecs <= 0){
        output("ERROR: invalid command\n");
        return 0;
    }else if(nsecs >= 100){
        output("ERROR: too nsecs too large, must be < 100 seconds");
        return 0;
    }

    output("beginning accel wbb for %d secs\n", nsecs);
    wbb_accel(wbb, nsecs);

    return 0;
}

static int server_handler(wbb_t * wbb, char * arg){
    wbb_server(wbb);
    return 0;
}

static wbb_cmd_t * get_matching_cmd(char * buf){
    for(wbb_cmd_t * curr = commands; *((unsigned *) curr) != 0; curr++){
        if(strncmp(curr->name, buf, curr->name_len) == 0){
            return curr;
        }
    }
    return NULL;
}

static int maybe_command(char * buf, unsigned size){
    if(buf[size - 1] == '\n'){
        return 1;
    }else{
        return 0;
    }
}

// returns 1 if we should quit.
static int try_execute_command(char * buf, wbb_t * wbb){
    wbb_cmd_t * possible_cmd = get_matching_cmd(buf);
    if(possible_cmd){
        return handler_wrapper(possible_cmd, buf, wbb);
    }else{
        output("ERROR: invalid command\n");
        return 0;
    }
}

void wbb_shell(wbb_t * wbb){
    print_cmds();
    output(">");
    char buf[MAX_CMD_SIZE];
    unsigned buf_size = 0;
    while(1){
        while(!uart_has_data()){/* wait for more data */}
        buf[buf_size++] = uart_getc();

        if(buf_size == MAX_CMD_SIZE){
            output("ERROR: command too long\n");
            buf_size = 0;
            output(">");
        }

        if(maybe_command(buf, buf_size)){
            buf[buf_size - 1] = 0;
            unsigned quit = try_execute_command(buf, wbb);
            if(quit){
                return;
            }
            buf_size = 0;
            output(">");
        }
    }
}
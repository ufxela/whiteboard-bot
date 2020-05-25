#include "wbb-extra.h"

static void wbb_go_down(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, 0, -1 * wbb->font_px);
}

static void wbb_go_up(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, 0, 1 * wbb->font_px);
}

static void wbb_go_right(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, 1 * wbb->font_px, 0);
}

static void wbb_go_left(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, -1 * wbb->font_px, 0);
}

static void wbb_go_diag_up_right(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, 1 * wbb->font_px, 1 * wbb->font_px);
}

static void wbb_go_diag_down_left(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, -1 * wbb->font_px, -1 * wbb->font_px);
}

static void wbb_go_diag_down_right(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, 1 * wbb->font_px, -1 * wbb->font_px);
}

static void wbb_go_diag_up_left(wbb_t * wbb){
    wbb_go_to_coords_relative(wbb, -1 * wbb->font_px, 1 * wbb->font_px);
}

static void wbb_draw_A(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_B(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_C(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_D(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_go_diag_down_left(wbb);
    wbb_go_up(wbb);
    wbb_lift_pen(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_E(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_F(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_G(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_H(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_I(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_J(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
}

static void wbb_draw_K(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_diag_up_right(wbb);
    wbb_go_diag_down_left(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_L(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);   
    wbb_go_down(wbb);    
    wbb_go_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_M(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_N(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_O(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);   
    wbb_go_down(wbb);   
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);   
    wbb_go_right(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_P(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_Q(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);   
    wbb_go_down(wbb);   
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);   
    wbb_go_right(wbb);
    wbb_go_diag_up_left(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_R(wbb_t * wbb){
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_S(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_T(wbb_t * wbb){
    wbb_lift_pen(wbb);
    wbb_go_right(wbb);
    wbb_place_pen(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
    wbb_go_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_down(wbb);
}

static void wbb_draw_U(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
}

static void wbb_draw_V(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
}

static void wbb_draw_W(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
}

static void wbb_draw_X(wbb_t * wbb){
    wbb_lift_pen(wbb);
    wbb_go_right(wbb);
    wbb_place_pen(wbb);
    wbb_go_diag_up_left(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_go_diag_down_left(wbb);
    wbb_go_diag_up_right(wbb);
    wbb_go_diag_up_right(wbb);
    wbb_go_diag_down_left(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_Y(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);
}

static void wbb_draw_Z(wbb_t * wbb){
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_down(wbb);
    wbb_go_right(wbb);
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_right(wbb);
}

static void wbb_draw_0(wbb_t * wbb){
    wbb_go_up(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_go_diag_down_right(wbb);
    wbb_go_diag_up_left(wbb);
    wbb_go_diag_up_left(wbb);
    wbb_go_right(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);   
    wbb_go_down(wbb);   
    wbb_go_left(wbb);
    wbb_go_left(wbb);
    wbb_go_up(wbb);
    wbb_go_down(wbb);   
    wbb_go_right(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_1(wbb_t * wbb){
    wbb_lift_pen(wbb);
    wbb_go_right(wbb);
    wbb_place_pen(wbb);
    wbb_go_up(wbb);
    wbb_go_diag_down_left(wbb);
    wbb_go_diag_up_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
    wbb_go_right(wbb);
    wbb_lift_pen(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_2(wbb_t * wbb){
    wbb_draw_Z(wbb);
}

static void wbb_draw_3(wbb_t * wbb){
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_left(wbb);
    wbb_go_right(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_4(wbb_t * wbb){
    wbb_go_right(wbb);
    wbb_go_up(wbb);
    wbb_go_diag_down_left(wbb);
    wbb_go_right(wbb);
    wbb_go_down(wbb);
    wbb_go_up(wbb);
}

static void wbb_draw_5(wbb_t * wbb){
    
}

static void wbb_draw_6(wbb_t * wbb){
    
}

static void wbb_draw_7(wbb_t * wbb){
    
}

static void wbb_draw_8(wbb_t * wbb){
    
}

static void wbb_draw_9(wbb_t * wbb){
    
}

static void wbb_draw_space(wbb_t * wbb){
    wbb_lift_pen(wbb);
    wbb_go_right(wbb);
    wbb_go_right(wbb);
    wbb_place_pen(wbb);
}

static void wbb_draw_new_line(wbb_t * wbb){
    wbb_lift_pen(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_go_down(wbb);
    wbb_place_pen(wbb);
}

static void wbb_draw_carriage_return(wbb_t * wbb){
	int x = wbb_get_pos(wbb).x;
    wbb_lift_pen(wbb);
    while(x > 0){
        wbb_go_left(wbb);
    }
    while(x < 0){
        wbb_go_right(wbb);
    }
    wbb_place_pen(wbb);
}

static void wbb_draw_letter(wbb_t * wbb, char letter){
    wbb_place_pen(wbb);
    switch(letter){
        case 'A':
            wbb_draw_A(wbb);
            break;
        case 'B':
            wbb_draw_B(wbb);
            break;
        case 'C':
            wbb_draw_C(wbb);
            break;
        case 'D':
            wbb_draw_D(wbb);
            break;
        case 'E':
            wbb_draw_E(wbb);
            break;
        case 'F':
            wbb_draw_F(wbb);
            break;
        case 'G':
            wbb_draw_G(wbb);
            break;
        case 'H':
            wbb_draw_H(wbb);
            break;
        case 'I':
            wbb_draw_I(wbb);
            break;
        case 'J':
            wbb_draw_J(wbb);
            break;
        case 'K':
            wbb_draw_K(wbb);
            break;
        case 'L':
            wbb_draw_L(wbb);
            break;
        case 'M':
            wbb_draw_M(wbb);
            break;
        case 'N':
            wbb_draw_N(wbb);
            break;
        case 'O':
            wbb_draw_O(wbb);
            break;
        case 'P':
            wbb_draw_P(wbb);
            break;
        case 'Q':
            wbb_draw_Q(wbb);
            break;
        case 'R':
            wbb_draw_R(wbb);
            break;
        case 'S':
            wbb_draw_S(wbb);
            break;
        case 'T':
            wbb_draw_T(wbb);
            break;
        case 'U':
            wbb_draw_U(wbb);
            break;
        case 'V':
            wbb_draw_V(wbb);
            break;
        case 'W':
            wbb_draw_W(wbb);
            break;
        case 'Y':
            wbb_draw_Y(wbb);
            break;
        case 'X':
            wbb_draw_X(wbb);
            break;
        case 'Z':
            wbb_draw_Z(wbb);
            break;
        case '\n':
            wbb_draw_new_line(wbb);
            break;
        case ' ':
            wbb_draw_space(wbb);
            break;
        case '\r':
            wbb_draw_carriage_return(wbb);
            break;
        case '0':
            wbb_draw_0(wbb);
            break;
        case '1':
            wbb_draw_1(wbb);
            break;
        case '2':
            wbb_draw_2(wbb);
            break;
        case '3':
            wbb_draw_3(wbb);
            break;
        case '4':
            wbb_draw_4(wbb);
            break;
        case '5':
            wbb_draw_5(wbb);
            break;
        case '6':
            wbb_draw_6(wbb);
            break;
        case '7':
            wbb_draw_7(wbb);
            break;
        case '8':
            wbb_draw_8(wbb);
            break;
        case '9':
            wbb_draw_9(wbb);
            break;        
        default:
            printk("letter: %c%d\n", letter, letter);
            unimplemented();
    }
    wbb_lift_pen(wbb);
}

void wbb_go_home(wbb_t * wbb){
    wbb_lift_pen(wbb);
    wbb_go_to_coords(wbb, 0, 0);
}

void wbb_draw_letters(wbb_t * wbb, char * letters){
    int index = 0;
    while(letters[index] != 0){
        wbb_draw_letter(wbb, letters[index]);
        wbb_go_right(wbb);
        index++;
    }
}
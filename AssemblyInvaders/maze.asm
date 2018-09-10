;%include "/usr/local/share/csc314/asm_io.inc"


; the file that stores the initial state
%define BOARD_FILE 'board.txt'
%define TITLE_FILE 'title.txt'
%define END_FILE 'end.txt'
; how to represent everything
%define WALL_CHAR '#'
%define PLAYER_CHAR "<-^->"

;%define TICK 30000
; the size of the game screen in characters
%define HEIGHT 31
%define WIDTH 63
; the player starting position.
; top left is considered (0,0)
%define STARTX 53
%define STARTY 1

; these keys do things
%define RESTART 'r'
%define EXITCHAR 'x'
;%define UPCHAR 'w'
%define LEFTCHAR ','
;%define DOWNCHAR 's'
%define RIGHTCHAR '.'
%define FIRE ' '
%define COLOR 'c'
%define NOCOLOR 'v'
segment .data
        TICK dd 30000
        RED db 27,91,48,59,51,49,109,0
        BRED db 27,91,49,59,51,49,109,0
        GREEN db 27,91,48,59,51,50,109,0
        BGREEN db 27,91,49,59,51,50,109,0
        YELLOW db 27,91,48,59,51,51,109,0
        BYELLOW db 27,91,49,59,51,51,109,0
        BLUE db 27,91,48,59,51,52,109,0
        BBLUE db 27,91,49,59,51,52,109,0
        MAGENTA db 27,91,48,59,51,53,109,0
        BMAGENTA db 27,91,49,59,51,53,109,0
        CYAN db 27,91,48,59,51,54,109,0
        BCYAN db 27,91,49,59,51,54,109,0
        WHITE db 27,91,48,109,0
        farRight dd 0
        farLeft dd 0
        numAlien dd 55
        Score dd 0
        af1x dd 0
        af1y dd 0
        af2x dd 0
        af2y dd 0
        playerLives dd 3
        firex dd 0
        firey dd 0
        credits dd 0
        alienmovementspeed dd 36
        xdirection dd 1
        ydirection dd 0
        lastscorecheck dd 1000
        tmp dd 0
        END dd 0
        numgames dd 0
        alienmoveseed dd 5
        alienlastcompare dd 50
        sp1 db "<o o>", 0
        r1 db "=0=", 0
        g1 db "<0>", 0
        b2 db "/0\", 0
        Player db "<-^->",0
        alienFireSpeed dd 0
        color_mode dd 0
        ; used to fopen() the board file defined above
        board_file                      db BOARD_FILE,0
        start_file                      db TITLE_FILE,0
        end_file                        db END_FILE,0
        ; used to change the terminal mode
        mode_r                          db "r",0
        raw_mode_on_cmd         db "stty raw -echo",0
        raw_mode_off_cmd        db "stty -raw echo",0

        ; called by system() to clear/refresh the screen
        clear_screen_cmd        db "clear",0

        ; things the program will print
        help_str                        db 13,10,"Controls: ", \
                                                        LEFTCHAR,"=LEFT / ", \
                                                        RIGHTCHAR,"=RIGHT / ", \
                                                        EXITCHAR,"=EXIT", \
                                                        13,10,10,0
        finalscore db "                              Score: %d",13,10,0
        score db "SCORE:  %d",13,10,0
        fmt db "%d",10,13, 0
        playerlives db "  %d  ",0
        playersymbol db " %s",0
segment .bss

        ; this array stores the current rendered gameboard (HxW)
        board   resb    (HEIGHT * WIDTH)

        ; these variables store the current player position
        xpos    resd    1
        ypos    resd    1
        aliens  resd    110
        shield resd 152
segment .text

        global  asm_main
        extern  system
        extern  putchar
        extern  getchar
        extern  printf
        extern  fopen
        extern  fread
        extern  fgetc
        extern  fclose
        extern  puts
        extern usleep
        extern fcntl
        extern rand
        extern srand
        extern sleep
        extern time
asm_main:
        enter   0,0
        pusha
        ;***************CODE STARTS HERE***************************
        push ebp
        mov ebp, esp
        ; put the terminal in raw mode so the game works nicely
        call    raw_mode_on


        call init_start
        start_screen:
        call start_render
        call getchar
        ; read the game board file into the global variable
        newgame:
        call    init_board
        push 0
        push time
        call srand
        add esp, 8
        ; set the player at the proper start position
        mov             DWORD [xpos], STARTX
        mov             DWORD [ypos], 29

        ;sub esp, 8
        ; the game happens in this loop
        ; the steps are...
        ;   1. render (draw) the current board
        ;   2. get a character from the user
        ;       3. store current xpos,ypos in esi,edi
        ;       4. update xpos,ypos based on character from user
        ;       5. check what's in the buffer (board) at new xpos,ypos
        ;       6. if it's a wall, reset xpos,ypos to saved esi,edi
        ;       7. otherwise, just continue! (xpos,ypos are ok)
        game_loop:

                mov eax, DWORD[Score]
                cmp eax, DWORD[lastscorecheck]
                jl noextralives
                inc DWORD[playerLives]
                add DWORD[lastscorecheck], 1000
                noextralives:
                cmp DWORD[playerLives], 0
                je end_game
                cmp DWORD[numAlien], 0
                jne not_refresh
                call refresh_game
                not_refresh:



                        push DWORD[TICK]
                        call usleep
                        add esp, 4


                ; draw the game board
                call    render
                cmp DWORD[END], 1
                je end_game
                ;;;;;;;;;;change alien locations in alien array



                ; get an action from the user
                call    nonblocking_getchar
                cmp al, -1
                je game_loop
        ;       call getchar
                ;jmp game_loop

                ; store the current position
                ; we will test if the new position is legal
                ; if not, we will restore these
                mov             esi, [xpos]
                mov             edi, [ypos]

                ; choose what to do
                cmp             eax, EXITCHAR
                je              end_game
                cmp             eax, RESTART
                je              refresh
                cmp             eax, FIRE
                je              fire
                cmp             eax, LEFTCHAR
                je              move_left
                cmp             eax, RIGHTCHAR
                je              move_right
                cmp             eax, COLOR
                je              set_color
                cmp             eax, NOCOLOR
                je              No_color
                jmp             input_end                       ; or just do nothing

                ; move the player according to the input character
                refresh:
                        mov DWORD[Score], 0
                        mov DWORD[playerLives], 3
                        mov DWORD[firey], 0
                        mov DWORD[af1y], 0
                        mov DWORD[alienmovementspeed], 36
                        jmp newgame
                set_color:
                ;       mov DWORD[TICK], 45000
                        mov DWORD[color_mode], 1
                        jmp game_loop
                No_color:
                        mov DWORD[TICK], 30000
                        mov DWORD[color_mode], 0
                        jmp game_loop
                fire:
                        cmp DWORD[firey], 0
                        jne game_loop
                        mov eax, DWORD[xpos]
                        mov DWORD[firex], eax
                        add DWORD[firex], 2
                        mov DWORD[firey], 29

                        jmp game_loop
                move_left:
                        cmp DWORD[xpos], 0
                        je input_end
                        dec             DWORD [xpos]
                        jmp             input_end
                move_down:
                        inc             DWORD [ypos]
                        jmp             input_end
                move_right:
                        cmp DWORD[xpos], WIDTH-5
                        je input_end
                        inc             DWORD [xpos]
                input_end:
                ;mov eax, DWORD [xpos]
                ;mov DWORD [ebp - 12], eax
                ; (W * y) + x = pos

                ; compare the current position to the wall character
                mov             eax, WIDTH
                mul             DWORD [ypos]
                add             eax, [xpos]
                lea             eax, [board + eax]
                cmp             BYTE [eax], WALL_CHAR
                jne             valid_move
                        ; opps, that was an invalid move, reset
                        mov             DWORD [xpos], esi
                        mov             DWORD [ypos], edi
                valid_move:

        jmp             game_loop
        end_game:
                call init_end
                call end_render



        game_loop_end:

        ; restore old terminal functionality
        call raw_mode_off
        mov esp, ebp
        pop ebp
        ;***************CODE ENDS HERE*****************************
        popa
        mov             eax, 0
        leave
        ret

; === FUNCTION ===
raw_mode_on:

        push    ebp
        mov             ebp, esp

        push    raw_mode_on_cmd
        call    system
        add             esp, 4

        mov             esp, ebp
        pop             ebp
        ret

; === FUNCTION ===
raw_mode_off:

        push    ebp
        mov             ebp, esp

        push    raw_mode_off_cmd
        call    system
        add             esp, 4

        mov             esp, ebp
        pop             ebp
        ret
refresh_game:
        push ebp
        mov ebp, esp
        mov DWORD[alienmovementspeed], 30
        mov DWORD[numAlien], 55
        inc DWORD[numgames]
        mov DWORD[firey], 0
        mov DWORD[af1y], 0
        mov ecx, 150
        mov eax, 0
        try_this:
        mov BYTE[board + eax], 32
        inc eax
        loop try_this
        mov edi, 22
        mov eax, 0
        mov ebx, 1;starting height
        mov ecx, 10;starting bloxk right
        aliensone2:
        cmp ebx, 11
        jge aliensoneend2
        mov DWORD[aliens + eax*4], ebx;moving y and x into an array for alliens
        inc eax
        mov DWORD[aliens + eax*4], ecx
        inc eax
        add ecx, 4
        mov esi, eax
        cdq
        idiv edi
        cmp edx, 0
        mov eax, esi
        jne aliensnext2
        inc ebx
        inc ebx
        mov ecx, 10
        aliensnext2:
        jmp aliensone2
        aliensoneend2:
        call start_render
        mov esp, ebp
        pop ebp
        ret
end_render:
        push ebp
        mov ebp, esp
        push BGREEN
        call printf
        add esp,4
        sub esp, 8
        push clear_screen_cmd
        call system
        add esp, 4

        mov DWORD[ebp-4], 0
        y2:
        cmp DWORD[ebp-4], HEIGHT
        je y_end2
        cmp DWORD[ebp-4],13
        jne notheight
        push DWORD[Score]
        push finalscore
        call printf
        add esp, 8
        inc DWORD[ebp-4]
        jmp y2
                notheight:
                mov DWORD[ebp-8], 0
                x2:

                cmp DWORD[ebp-8], WIDTH
                je xend2


                        mov eax, [ebp-4]
                        mov ebx, WIDTH
                        mul ebx
                        add eax, [ebp-8]
                        mov ebx, 0
                        mov  bl, BYTE[board + eax]
                        push ebx
                call putchar
                add esp, 4
                inc DWORD[ebp-8]
                jmp x2
                xend2:
                push 0x0d
                call putchar
                add esp, 4
                push 0x0a
                call putchar
                add esp,4
        inc DWORD[ebp-4]
        jmp y2
        y_end2:

        push WHITE
        call printf
        mov esp, ebp
        pop ebp
        ret

start_render:
        push ebp
        mov ebp, esp
        push BGREEN
        call printf
        add esp,4
        sub esp, 8
        push clear_screen_cmd
        call system
        add esp, 4

        mov DWORD[ebp-4], 0
        y:
        cmp DWORD[ebp-4], HEIGHT
        je y_end
                mov DWORD[ebp-8], 0
                x:

                cmp DWORD[ebp-8], WIDTH
                je xend
                        mov eax, [ebp-4]
                        mov ebx, WIDTH
                        mul ebx
                        add eax, [ebp-8]
                        mov ebx, 0
                        mov  bl, BYTE[board + eax]
                        push ebx
                call putchar
                add esp, 4
                inc DWORD[ebp-8]
                jmp x
                xend:
                push 0x0d
                call putchar
                add esp, 4
                push 0x0a
                call putchar
                add esp,4
        inc DWORD[ebp-4]
        jmp y
        y_end:

        push WHITE
        call printf
        mov esp, ebp
        pop ebp
        ret

init_end:
        push ebp
        mov ebp, esp
        sub esp, 8
        push mode_r
        push end_file
        call fopen
        add esp, 8
        mov DWORD[ebp-4], eax
        mov DWORD[ebp-8], 0
        rad_loop:
        cmp DWORD[ebp-8], 11
        je rad_loop_end
                mov eax,WIDTH
                mul DWORD[ebp-8]
                lea ebx, [board + eax]

                push DWORD[ebp-4]
                push WIDTH
                push 1
                push ebx
                call fread
                add esp, 16
                push DWORD[ebp-4]
                call fgetc
                add esp, 4
        inc DWORD[ebp-8]
        jmp rad_loop
        rad_loop_end:

        push DWORD[ebp-4]
        call fclose
        add esp, 4


        push WHITE
        call printf
        add esp, 4
        mov esp, ebp
        pop ebp
        ret


init_start:
        push ebp
        mov ebp, esp
        sub esp, 8
        push mode_r
        push start_file
        call fopen
        add esp, 8
        mov DWORD[ebp-4], eax
        mov DWORD[ebp-8], 0
        red_loop:
        cmp DWORD[ebp-8], HEIGHT
        je red_loop_end

                mov eax, WIDTH
                mul DWORD[ebp-8]
                lea ebx, [board + eax]

                push DWORD[ebp-4]
                push WIDTH
                push 1
                push ebx
                call fread
                add esp, 16
                push DWORD[ebp-4]
                call fgetc
                add esp, 4
        inc DWORD[ebp-8]
        jmp red_loop
        red_loop_end:

        push DWORD[ebp-4]
        call fclose
        add esp, 4


        push WHITE
        call printf
        add esp, 4
        mov esp, ebp
        pop ebp
        ret


; === FUNCTION ===
init_board:

        push    ebp
        mov             ebp, esp

        ; FILE* and loop counter
        ; ebp-4, ebp-8
        sub             esp, 16

        ; open the file
        push    mode_r
        push    board_file
        call    fopen
        add             esp, 8
        mov             DWORD [ebp-4], eax

        ; read the file data into the global buffer
        ; line-by-line so we can ignore the newline characters
        mov             DWORD [ebp-8], 0
        read_loop:
        cmp             DWORD [ebp-8], HEIGHT
        je              read_loop_end

                ; find the offset (WIDTH * counter)
                mov             eax, WIDTH
                mul             DWORD [ebp-8]
                lea             ebx, [board + eax]

                ; read the bytes into the buffer
                push    DWORD [ebp-4]
                push    WIDTH
                push    1
                push    ebx
                call    fread
                add             esp, 16

                ; slurp up the newline
                push    DWORD [ebp-4]
                call    fgetc
                add             esp, 4

        inc             DWORD [ebp-8]
        jmp             read_loop
        read_loop_end:

        ; close the open file handle
        push    DWORD [ebp-4]
        call    fclose
        add             esp, 4
        ;add aliens to something
        mov edi, 22
        mov eax, 0
        mov ebx, 1;starting height
        mov ecx, 10;starting bloxk right
        aliensone:
        cmp ebx, 11
        jge aliensoneend
        mov DWORD[aliens + eax*4], ebx;moving y and x into an array for alliens
        inc eax
        mov DWORD[aliens + eax*4], ecx
        inc eax
        add ecx, 4
        mov esi, eax
        cdq
        idiv edi
        cmp edx, 0
        mov eax, esi
        jne aliensnext
        inc ebx
        inc ebx
        mov ecx, 10
        aliensnext:
        jmp aliensone
        aliensoneend:

        ;add shields to somethingi
        ;spent too much time on this to find a different way
;       mov edi, 12
;       mov eax, 0
;       mov ebx, 23; y
;       mov ecx, 8; x
;       mov edx, 6
;       sub esp, 4
;       shieldsloop:
;       cmp eax, 151
;       jge shieldsloopend
;
;
;       mov DWORD[shields + eax], ecx
;;      inc eax
;       mov DWORD[shields + eax], ebx
;       inc eax
;       inc ecx
;       cmp eax, 23
;       je increase_shield1
;       cmp eax, 63
;       je increase_shield2
;;      cmp eax, 119
;       je increase_shield2
;
;       mov DWORD[ebp - 4], eax
;       mov DWORD[ebp -8], ecx
;       mov ecx, edx
;       cdq
;       idiv ecx
;       cmp edx, 0
;       jne no_shield_space
;       cmp ebx, 23
;       je shield_first
;       cmp ebx, 24
;;      je shield_second
;       cmp ebx, 25
;       je shield_third
;       cmp ecx, 8
;       je shield_three
;       cmp ecx, 23
;       je shield_three
;       cmp ecx, 38
;       je shield_three
;       cmp ecx, 52
;       je shield_three
;
;       shield_eight:
;
;       no_shield_space:
;.;.....................
;
;
;       increase_shield2:
;       mov ecx, 6
;       jmp nise
;       increase_shield1:
;       mov ecx, 7

;;
;       nise:
;       inc ebx
;


;       shieldsloopend:

        mov             esp, ebp
        pop             ebp
        ret

; === FUNCTION ===
render:

        push    ebp
        mov             ebp, esp
        sub             esp, 8
        startover:
        ;working with alien fireing
        cmp DWORD[af1y], 0
        je not_30
        cmp DWORD[af1y], 30
        jl nofireone
        not_30:
        call rand
        cdq
        mov ecx, 55
        idiv ecx
        mov eax, edx
        imul eax,2
        findingalienloop:
        cmp DWORD[aliens + eax*4], -1
        je not_30
        mov ecx, DWORD[aliens + eax*4]
        mov DWORD[af1y], ecx
        inc eax
        mov ecx,DWORD[aliens + eax*4]
        inc ecx
        mov DWORD[af1x], ecx
        jmp nofireone
        ;jmp firetwo


        nofireone:
        ;inc DWORD[af1y]
        fireone:
        ;jmp firetwo
        ;inc DWORD[af1y]
        ;could delete this but i'll try to fix it, right now both rand values are the same
        ;cmp DWORD[af2y], 30
;       jl nofiretwo
;       call rand
;       push eax
;       call srand
;       add esp, 4
;       call rand
;       cdq
;       mov ecx, 55
;       idiv ecx
;       mov eax, edx
;       imul eax, 2
;       mov ecx, DWORD[aliens + eax*4]
;       mov DWORD[af2y], ecx
;       inc eax
;       mov ecx, DWORD[aliens + eax*4]
;       inc ecx
;       mov DWORD[af2x], ecx

;       jmp firetwo
        nofiretwo:
        ;inc DWORD[af2y]
        firetwo:
        ;working with alien movement
        inc DWORD[tmp]
        mov eax, 0
        mov ebx, 0
        mov DWORD[farLeft], 99
        mov DWORD[farRight], -1

        InsertingAliens:;loop through aliens array
                cmp eax, 110
                jge DoneInserting
        ;       mov ecx, HEIGHT
                ;dec ecx
                cmp DWORD[aliens + eax*4],29
                je endrender

                mov esi, DWORD[aliens + eax*4];this is why i used y,x for aliens
                inc eax
                mov edi, DWORD[aliens + eax*4]
                inc eax
                cmp esi, -1
                je InsertingAliens
                imul esi, WIDTH
                cmp edi, DWORD[farRight]
                jg farRightUpdate
                comingback:
                cmp edi, DWORD[farLeft]
                jl farLeftUpdate
                jmp goingback


                farRightUpdate:
                        mov DWORD[farRight], edi
                        jmp comingback
                farLeftUpdate:
                        mov DWORD[farLeft], edi


                goingback:
                ;add esi, edi
                sub eax, 2
                mov esi, DWORD[aliens + eax*4]
                inc eax
                imul esi, WIDTH
                add esi, DWORD[aliens + eax*4]
                inc eax
                mov ecx, 0
                BoardAliens:;loop through alien string
                        cmp ecx, 3
                        je DoneBoard
                        cmp eax, 66
                        jg r3
                        cmp eax, 22
                        jg r2
                        mov bl, BYTE[r1 + ecx]
                        jmp r4

                        r2:
                        mov bl, BYTE[g1 + ecx]

                        jmp r4
                        r3:
                ;       sub eax, 2
                ;       mov edx, DWORD[aliens + eax * 4]
                ;       mov bl, dl
                ;       add bl, 48
                ;       add eax, 2
                        mov bl, BYTE[b2 + ecx]

                        r4:

                                add esi, ecx
                                mov BYTE[board+esi], bl
                                sub esi, ecx
                                inc ecx
                                jmp BoardAliens


                DoneBoard:
                jmp InsertingAliens
        DoneInserting:
        mov eax, DWORD[alienmovementspeed]
        cmp eax, DWORD[tmp]
        jg nomove
        mov eax, 0
        clearBoard:
                cmp eax, WIDTH * HEIGHT
                jge doneclearing
                cmp BYTE[board + eax], 35
                je incrementeax
                cmp BYTE[board + eax], 95
                je incrementeax
                mov BYTE[board + eax], 32

                incrementeax:
                inc eax
                jmp clearBoard

        doneclearing:


        mov eax, WIDTH
        sub eax, 3
        cmp DWORD[farRight], eax
        je rightwall
        cmp DWORD[farLeft], 0
        jne nochange
                mov DWORD[xdirection], 1
                mov DWORD[ydirection], 1
                jmp nochange
        rightwall:
                mov DWORD[xdirection], -1
                mov DWORD[ydirection], 1

        nochange:
        ;Beggining with moving the enemies
        mov DWORD[tmp], 0
        mov eax, 0
        moveloop:
                cmp eax, 110
                jge donemove1
                mov ebx, DWORD[ydirection]
                cmp DWORD[aliens + eax*4], -1
                je nextAlien
                add DWORD[aliens + eax*4], ebx
                inc eax
                mov ebx, DWORD[xdirection]
                add DWORD[aliens + eax*4], ebx
                inc eax
                jmp moveloop
                nextAlien:
                inc eax
                inc eax
                jmp moveloop
        donemove1:
        jmp startover

        donemove:
        ; two ints, for two loop counters
        ; ebp-4, ebp-8

        ; clear the screen
        nomove:
        mov DWORD[ydirection], 0
;       push
        push    clear_screen_cmd
        call    system
        add             esp, 4

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        push DWORD[Score];DWORD[Score]
        push score
        call printf
        add esp, 8


        ; print the help information
        cmp DWORD[af1y], 30
        je zx
        cmp DWORD[alienFireSpeed], 0
        jne notinc
        inc DWORD[af1y]
        inc DWORD[alienFireSpeed]
        jmp xz
        notinc:
        dec DWORD[alienFireSpeed]
        jmp xz
        zx:
        mov DWORD[af1x], -1
        xz:
;       cmp DWORD[af2y], 30
        je zy
;       inc DWORD[af2y]
;       jmp yz
        zy:
;       mov DWORD[af2x], -1
        yz:
        cmp DWORD[firey], 0
        je notthiscommand
        dec DWORD[firey]
        jmp check_collision
        notthiscommand:
        mov DWORD[firex], -1

        check_collision:

        ; outside loop by height
        ; i.e. for(c=0; c<height; c++)
        mov             DWORD [ebp-4], 0
        y_loop_start:
        cmp             DWORD [ebp-4], HEIGHT
        je              y_loop_end

                ; inside loop by width
                ; i.e. for(c=0; c<width; c++)
                mov             DWORD [ebp-8], 0
                x_loop_start:
                cmp DWORD[color_mode], 1
                jne no_color

                call rand
                cdq
                mov ebx, 12
                idiv ebx
                cmp edx, 0
                je a
                cmp edx, 1
                je b
                cmp edx, 2
                je c
                cmp edx, 3
                je d
                cmp edx, 4
                je e
                cmp edx, 5
                je f
                cmp edx, 6
                je g
                cmp edx, 7
                je h
                cmp edx, 8
                je i
                cmp edx, 9
                je j
                cmp edx, 10
                je k
                push RED
                jmp l
                k:
                push BRED
                jmp l
                j:
                push GREEN
                jmp l
                i:
                push BGREEN
                jmp l
                h:
                push YELLOW
                jmp l
                g:
                push BYELLOW
                jmp l
                f:
                push CYAN
                jmp l
                e:
                push BLUE
                jmp l
                d:
                push BBLUE
                jmp l
                c:
                push MAGENTA
                jmp l
                b:
                push BMAGENTA
                jmp l
                a:
                push BCYAN
                l:
                call printf
                add esp, 4

                no_color:

                cmp             DWORD [ebp-8], WIDTH
                je              x_loop_end

                        ; check if (xpos,ypos)=(x,y)
                        mov             eax, [xpos]
                        cmp             eax, DWORD [ebp-8]
                        jne             print_board
                        mov             eax, [ypos]
                        cmp             eax, DWORD [ebp-4]
                        jne             print_board
                                ; if both were equal, print the player
                                ;push   Player
                                jmp             print_player
                        print_board:
                                ; otherwise print whatever's in the buffer

                                ;check for bullet
                                mov eax, [af1x]
                                cmp eax, DWORD[ebp-8]
                                jne checkplayerbullet
                                mov eax, [af1y]
                                cmp eax, DWORD[ebp-4]
                                jne checkplayerbullet
                                mov al, 58
                                push eax
                                jmp print_end

                        ;       checkalien2bullet:
                        ;       mov eax, [af1x]
                        ;       cmp eax, DWORD[ebp-8]
                        ;       jne checkplayerbullet
                        ;       mov eax, [af1y]
                        ;       cmp eax, DWORD[ebp-4]
                        ;       jne checkplayerbullet
                        ;       mov al, 58
                        ;       push eax
                        ;       jmp print_end

                                checkplayerbullet:
                                mov eax, [firex]
                                cmp eax, DWORD[ebp-8]
                                jne pbnext
                                mov eax, [firey]
                                cmp eax, DWORD[ebp-4]
                                jne pbnext
                                mov al, 33
                                push eax
                                jmp print_end

                                pbnext:
                                mov             eax, [ebp-4]
                                mov             ebx, WIDTH
                                mul             ebx
                                add             eax, [ebp-8]
                                mov             ebx, 0
                                mov             bl, BYTE [board + eax]
                                cmp bl, 35
                                jne nogreen
                                push GREEN
                                call printf
                                add esp, 4
                                nogreen:
                                push    ebx
                        print_end:
                        call    putchar
                        add             esp, 4
                        jmp print_end_end

                        print_player:
                        push Player
                        call printf
                        add esp, 4
                        add DWORD[ebp-8], 4
                        print_end_end:

                inc             DWORD [ebp-8]
                jmp             x_loop_start
                x_loop_end:

                ; write a carriage return (necessary when in raw mode)
                push    0x0d
                call    putchar
                add             esp, 4

                ; write a newline
                push    0x0a
                call    putchar
                add             esp, 4

        inc             DWORD [ebp-4]
        jmp             y_loop_start
        y_loop_end:


        ;check for bullet and collision
        cmp DWORD[firey], 0
        je no_collision
        mov eax, [firey]
        imul eax, WIDTH
        add eax, [firex]
;       mov bl, BYTE [board + eax]

        cmp BYTE[board + eax], 35
        je collision_with_shield
        sub eax, WIDTH
        cmp BYTE[board + eax], 58
        je collision_with_AlienBullet
        add eax, WIDTH
        cmp BYTE[board + eax], 58
        je collision_with_AlienBullet
        mov edi, DWORD[firex]
        cmp edi, DWORD[af1x]
        jne not_bullets
        mov edi, DWORD[firey]
        cmp edi, DWORD[af1y]
        jg not_bullets
        sub edi, 4
        ;cmp edi, DWORD[af1y]
        ;jl not_bullets
        jmp collision_with_AlienBullet
        not_bullets:
        cmp BYTE[board + eax], 32
        je no_collision

        collision_with_alien:
        dec eax
        cmp BYTE[board + eax], 32
        je subbed_one
        dec eax
        cmp BYTE[board + eax], 32
        je subbed_one
        jmp sub_none
        subbed_one:
        inc eax
        sub_none:;eax should point to the first character of the alien that got hit
        mov edi, eax
        mov ebx, [firey]
        imul ebx, WIDTH
        sub eax, ebx ; eax equals x
        mov ecx, 0
        findAlienloop:
        cmp ecx, 112
        je broken
        ;mov DWORD[score], eax
        mov ebx, [firey]
        cmp DWORD[aliens + ecx*4], ebx
        je ys_match
        inc ecx
        inc ecx
        jmp findAlienloop
        ys_match:
        inc ecx
        cmp DWORD[aliens+ ecx*4], eax
        je itsamatch
        inc ecx
        jmp findAlienloop
        itsamatch:
        dec DWORD[numAlien]
        dec ecx
        mov DWORD[aliens+ecx*4], -1
        mov eax, edi
        mov BYTE[board + eax], 32
        inc eax
        mov BYTE[board + eax], 32
        inc eax
        mov BYTE[board + eax], 32
        mov DWORD[firey], 0
        cmp ecx, 66
        jg s3
        cmp ecx, 22
        jg s2
        add DWORD[Score], 30
        jmp s4

        s2:
        add DWORD[Score], 20
        jmp s4

        s3:
        add DWORD[Score], 10




        s4:
        cmp DWORD[numAlien], 50
        jge fifty
        cmp DWORD[numAlien], 40
        jge forty
        cmp DWORD[numAlien], 25
        jge twenty
        cmp DWORD[numAlien], 8
        jge eight
        cmp DWORD[numAlien], 2
        jge two
        mov DWORD[alienmovementspeed], 2
        jmp no_increase
        two:
        mov DWORD[alienmovementspeed], 4
        jmp no_increase
        eight:
        mov DWORD[alienmovementspeed], 8
        jmp no_increase
        twenty:
        mov DWORD[alienmovementspeed], 16
        jmp no_increase
        forty:
        mov DWORD[alienmovementspeed], 24
        jmp no_increase
        fifty:
        mov DWORD[alienmovementspeed], 30
        ;mov eax, DWORD[alienlastcompare]
        ;cmp eax, DWORD[numAlien]
        ;jne no_increase
        ;       sub DWORD[alienlastcompare], 4
;               sub DWORD[alienmovementspeed], 4
        no_increase:
        mov eax, DWORD[numgames]
        mov ebx, 2
        imul ebx
        sub DWORD[alienmovementspeed], eax
        cmp DWORD[alienmovementspeed], 2
        jge no_collision
        mov DWORD[alienmovementspeed], 2
        jmp no_collision

        broken:
        add DWORD[firey], 10
        jmp no_collision

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        collision_with_AlienBullet:
        ;mov eax, DWORD[firey]
        ;cmp DWORD[af1y], eax
        ;jne no_collision
        mov DWORD[af1y], 0
        mov DWORD[firey], 0
        mov BYTE[board + eax], 176
        ;jmp done_with_this_collision
;       collided_with_2:
;       mov DWORD[af2y], 0
;       done_with_this_collision:
;       mov DWORD[firey], 0
;       mov BYTE [board + eax], 176


        collision_with_shield:
        mov DWORD[firey], 0
        mov BYTE [board + eax], 32


        jmp no_collision
        endrender:
        mov DWORD[END], 1


        no_collision:
;;;;;;;;;;;;;;;;;;;;aliens bullet turn
        cmp DWORD[af1y], 30
        je no_collision_af1
        mov eax, [af1y]
        imul eax, WIDTH
        add eax, [af1x]

        cmp BYTE[board + eax], 35
        jne af1noshield
;       mov eax, ebx
;       call getchar
;       mov ebx, eax
        mov DWORD[af1y], 0
        mov BYTE[board + eax], 32
        af1noshield:
        mov eax, DWORD[af1y]
        cmp eax, DWORD[ypos]
        jne no_collision_af1
        mov ebx, DWORD[xpos]
        cmp DWORD[af1x], ebx
        jl no_collision_af1
        add ebx,4
        cmp DWORD[af1x], ebx
        jg no_collision_af1
        ;collision with player
        call Player_Death









        no_collision_af1:

;       cmp DWORD[af2y], 0
;       je no_collision_af2
;       mov eax, [af2y]
;       imul eax, WIDTH
;       add eax, [af2x]

;       cmp BYTE[board + eax], 35
;       jne af2noshield
;       mov DWORD[af2y], 0
;       mov BYTE[board + eax], 32
;       af2noshield:




        no_collision_af2:

        push DWORD[playerLives]
        push playerlives
        call printf
        add esp, 8
        cmp DWORD[playerLives], 1
        je nomorelives
        cmp DWORD[playerLives], 2
        je onemorelife
        push Player
        push playersymbol
        call printf
        add esp, 8
        onemorelife:
        push Player
        push playersymbol
        call printf
        add esp, 8
        nomorelives:
        push WHITE
        call printf
        add esp, 4




        mov             esp, ebp
        pop             ebp
        ret

Player_Death:

        push ebp
        mov ebp, esp
        dec DWORD[playerLives]
        mov DWORD[af1y], 0
        mov DWORD[firey], 0
        push BRED
        call printf
        add esp,4
        sub             esp, 8

        ; clear the screen
        push    clear_screen_cmd
        call    system
        add             esp, 4

        ; print the help information
        push DWORD[Score]
        push score
        call printf
        add esp, 8

       ; outside loop by height
        ; i.e. for(c=0; c<height; c++)
        mov             DWORD [ebp-4], 0
        y_loop_start2:
        cmp             DWORD [ebp-4], HEIGHT
        je              y_loop_end2

                ; inside loop by width
                ; i.e. for(c=0; c<width; c++)
                mov             DWORD [ebp-8], 0
                x_loop_start2:
                cmp             DWORD [ebp-8], WIDTH
                je              x_loop_end2

                        ; check if (xpos,ypos)=(x,y)
                        mov             eax, [xpos]
                        cmp             eax, DWORD [ebp-8]
                        jne             print_board2
                        mov             eax, [ypos]
                        cmp             eax, DWORD [ebp-4]
                        jne             print_board2
                                ; if both were equal, print the player
                                mov ecx, 0
                                push eax
                                push ebx
                                jmp             print_death2
                        print_board2:
                                ; otherwise print whatever's in the buffer
                                mov             eax, [ebp-4]
                                mov             ebx, WIDTH
                                mul             ebx
                                add             eax, [ebp-8]
                                mov             ebx, 0
                                mov             bl, BYTE [board + eax]
                                push    ebx
                        print_end2:
                        call    putchar
                        add             esp, 4
                        jmp notDeath

                        print_death2:
                        cmp ecx, 4
                        je notDeath1

                        mov esi, ecx
                        call rand
                        push eax
                        call putchar
                        add esp, 4
                        mov ecx, esi
                        inc DWORD[ebp-8]
                        inc ecx
                        jmp print_death2

                notDeath1:
                dec DWORD[ebp-8]
                pop ebx
                pop eax
                notDeath:
                inc             DWORD [ebp-8]
                jmp             x_loop_start2
                x_loop_end2:

                ; write a carriage return (necessary when in raw mode)
                push    0x0d
                call    putchar
                add             esp, 4

                ; write a newline
                push    0x0a
                call    putchar
                add             esp, 4

        inc             DWORD [ebp-4]
        jmp             y_loop_start2
        y_loop_end2:


        push 0
        push time
        call srand
        add esp, 8


        push 1
        call sleep
        add esp, 4
        push 20
        push time


        call srand
        add esp,8
        mov esp, ebp
        pop ebp
        ret
nonblocking_getchar:

; returns -1 on no-data
; returns char on succes

; magic values
%define F_GETFL 3
%define F_SETFL 4
%define O_NONBLOCK 2048
%define STDIN 0

        push    ebp
        mov             ebp, esp

        ; single int used to hold flags
        ; single character (aligned to 4 bytes) return
        sub             esp, 8

        ; get current stdin flags
        ; flags = fcntl(stdin, F_GETFL, 0)
        push    0
        push    F_GETFL
        push    STDIN
        call    fcntl
        add             esp, 12
        mov             DWORD [ebp-4], eax

        ; set non-blocking mode on stdin
        ; fcntl(stdin, F_SETFL, flags | O_NONBLOCK)
        or              DWORD [ebp-4], O_NONBLOCK
        push    DWORD [ebp-4]
        push    F_SETFL
        push    STDIN
        call    fcntl
        add             esp, 12

        call    getchar
        mov             DWORD [ebp-8], eax

        ; restore blocking mode
        ; fcntl(stdin, F_SETFL, flags ^ O_NONBLOCK
        xor             DWORD [ebp-4], O_NONBLOCK
        push    DWORD [ebp-4]
        push    F_SETFL
        push    STDIN
        call    fcntl
        add             esp, 12

        mov             eax, DWORD [ebp-8]

        mov             esp, ebp
        pop             ebp
        ret


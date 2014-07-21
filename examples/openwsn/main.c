#include <stdio.h>

#include "vtimer.h"
#include "shell.h"
#include "posix_io.h"
#include "openwsn.h"
#include "board_uart0.h"

int main(void) {
    shell_t shell;

    posix_open(uart0_handler_pid, 0);

    puts("Welcome to RIOT!");

    shell_init(&shell, NULL, UART0_BUFSIZE, uart0_readc, uart0_putc);

    shell_run(&shell);

    return 0;
}

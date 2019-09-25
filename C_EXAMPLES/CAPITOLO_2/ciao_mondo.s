# ----------------------------------------------------------------------------------------
# Scirve "Ciao, mondo!" nel terminale usando chiamate di sistema using only system calls 
# Per compilare ed eseguire in MAC OSX
#
#     gcc ciao_mondo.s && ./a.out
#
# in linux:
#     gcc -DLINUX_OS ciao_mondo.s && ./a.out
#
# ----------------------------------------------------------------------------------------
 
        .data 

#ifdef LINUX_OS
        write_syscall= 60
        exit_syscall= 1
#else
        write_syscall= 0x2000004
        exit_syscall= 0x2000001
#endif

message:
        .ascii  "Ciao, mondo!\n"
        len = . - message #indirizzo attuale - quello message 

        .text
        .global _main

_main:
        # write(1, message, len)
        #
        # mov -> 16 bit; movl -> 32 bit; movq -> 64 bit
        #
        # mov label, reg:       copia il valore corrispondente all'indirizzo di 'label' nel registro reg
        #
        # mov $const, reg:      copia la costante 'const' nel registro 'reg'
        #
        # mov $label, reg:      copia l'indirizzo della variabile 'label' in 'reg'
        #
        # leaq label, reg:      copia l'indirizzo di label nel registro reg
        #
        movl    $write_syscall, %eax    # chiamata di sistema 0x20000004 ($1 in linux) ovvero scrivi su schermo
        movl    $1, %edi                # 1 è standard out (stdout)
        leaq    message(%rip), %rsi     # metto nel registro %rsi l'indirizzo della stringa da stampare
        movq    $len, %rdx              # metto in %rdx il numero di bytes da stampare (lungh. stringa + 1), len è una costante!
        syscall                         # effettua la chiamata di sistema

        # exit(0)
        movl     $0, %edi               # metto il codice da ritornare alla shell nel registro $edi
        movl     $exit_syscall, %eax       # metto in %eax il valore 0x2000001 ($60 in linux) ovvero exit()
        syscall                         # effettua la chiamata di sistema


/*
** EPITECH PROJECT, 2018
** My Put Nbr
** File description:
** Desc
*/

#include "my.h"

int my_put_nbr(int nb)
{
    int nb2;

    if (nb < 0) {
        my_putchar('-');
        if (nb == -2147483648) {
            my_putchar(2);
            my_put_nbr(147483648);
        } else {
            nb = (-1) * nb;
            my_put_nbr(nb);
        }
    } else if (nb >= 10) {
        nb2 = nb % 10;
        nb = nb - nb2;
        nb = nb / 10;
        my_put_nbr(nb);
        my_putchar(nb2 + 48);
    } else {
        my_putchar(nb + 48);
    }
    return (0);
}

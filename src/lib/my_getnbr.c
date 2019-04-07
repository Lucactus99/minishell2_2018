/*
** EPITECH PROJECT, 2018
** d
** File description:
** d
*/

int my_strlen2(char *str)
{
    int value = 0;

    while (str[value] == '-' || str[value] == '+')
        value++;
    while (str[value] != '\0' && str[value] >= 48 && str[value] <= 57)
        value++;
    return (value);
}

int my_power_it(int nb, int power)
{
    int begin = 0;
    int actual_nbr = 1;

    if (power >= 0) {
        while (begin < power) {
            begin++;
            actual_nbr *= nb;
        }
        return (actual_nbr);
    } else
        return (0);
}

int calc_nbr(int value, int lenght, char *str)
{
    int actual_nbr = 0;

    while (str[value] != 0 && str[value] >= 48 && str[value] <= 57) {
        actual_nbr += (str[value] - 48) * my_power_it(10, lenght);
        lenght--;
        value++;
    }
    return (actual_nbr);
}

int int_limit(char *str)
{
    char cmp1[] = "2147483647";
    char cmp2[] = "2147483648";
    int value = 0;
    int value2 = 0;

    if (my_strlen2(str) < my_strlen2(cmp1))
        return (1);
    if (str[0] != '-') {
        while (cmp1[value] != 0 && str[value] != 0 && cmp1[value] == str[value])
            value++;
        return (cmp1[value] - str[value]);
    } else {
        value2++;
        while (cmp2[value] != 0 && str[value2] != 0 &&
        cmp2[value] == str[value2]) {
            value++;
            value2++;
        }
        return (cmp2[value] - str[value2]);
    }
}

int my_getnbr(char *str)
{
    int value = int_limit(str);
    int actual_nbr;
    int lenght = my_strlen2(str) - 1;
    int neg = 0;

    if (value < 0)
        return (0);
    value = 0;
    while (str[value] == '-' || str[value] == '+') {
        if (str[value] == '-')
            neg++;
        value++;
    }
    lenght -= value;
    actual_nbr = calc_nbr(value, lenght, str);
    if (neg % 2 == 1)
        actual_nbr = -actual_nbr;
    return (actual_nbr);
}
/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** get speed from level
*/

int high_speed(int level)
{
    if (level < 13)
        return (5);
    if (level < 16)
        return (4);
    if (level < 19)
        return (3);
    if (level < 29)
        return (2);
    return (1);
}

int get_speed(int level)
{
    switch (level){
    case 0: return (48);
    case 1: return (43);
    case 2: return (38);
    case 3: return (33);
    case 4: return (28);
    case 5: return (23);
    case 6: return (18);
    case 7: return (13);
    case 8: return (8);
    case 9: return (6);
    default: break;
    }
    return (high_speed(level));
}

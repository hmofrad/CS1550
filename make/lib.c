/* 
 * Strcpy and strcat using char pointer arithmetic
 * (C) Mohammad H. Mofrad, 2016
 *   
 */

void my_strcpy(char *dest, char *src) {
    while(*dest++ = *src++);
}
void my_strcat(char *dest, char *src) {
    while(*dest++);
    *dest--;
    my_strcpy(dest, src);
}

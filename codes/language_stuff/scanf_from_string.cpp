char sentence[] = "Rudolph is 12 years old";
char str[20];
int i;
sscanf(sentence, "%s %*s %d", str, &i);
printf("%s -> %d\n", str, i);
// Output: Rudolph -> 12
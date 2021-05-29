
int validWordAbbreviation(char* s, char* abbr) {
    int len1 = strlen(s);
    int len2 = strlen(abbr);
    int i = 0, j = 0;
    while ( i < len1 && j < len2 ) {
        if (isalpha(abbr[j])) {
            if (s[i] == abbr[j]) {
                ++i;
                ++j;
            } else
                return 0;
        } else {
            if (abbr[j] == '0')
                return 0;
            int n = 0;
            while (isdigit(abbr[j]) && j < len2) {
                n = 10 * n + (abbr[j] - '0');
                ++j;
            }
            i += n;
        }
    }
    return i == len1 && j == len2;
}

int validWordAbbreviation2(char* word, char* abbr) {
    int k = 0, i = 0, len1 = strlen(word), len2 = strlen(abbr);
    while (i < len2) {
        if (word[k] == abbr[i]) {
            i++, k++;
            continue;
        }
        if (abbr[i] == '0')
            return 0;
        int cnt = 0;
        while (isdigit(abbr[i]))
            cnt = cnt * 10 + (abbr[i] - '0'), i++;
        k += cnt;
        if (k > len1 || word[k] != abbr[i])
            return 0;
    }
    return k == len1;
}

string manacher(const string& prototype) {
    if (prototype.size() > 0) {
        string Temp_String = "";
        for (auto str : prototype) {
            Temp_String += str;
            Temp_String += "#";
        }
        Temp_String = "@#" + Temp_String + "&";

        vector<ll> palindrome(Temp_String.size(), 0);
        ll bigger_center = 0;
        ll right = 0;
        for (ll i = 1; i < Temp_String.size() - 1; i++) {
            if (i < right) {
                ll opposite_to_i = 2 * bigger_center - i;
                palindrome[i] = min(palindrome[opposite_to_i], right - i);
            }
            while (Temp_String[i + (palindrome[i] + 1)] ==
                Temp_String[i - (palindrome[i] + 1)]) {
                palindrome[i]++;
            }

            if (i + palindrome[i] > right) {
                bigger_center = i;
                right = i + palindrome[i];
            }
        }
        ll half_length = 0;
        ll center_index = 0;

        for (ll i = 1; i < Temp_String.size() - 1; i++) {
            if (palindrome[i] > half_length) {
                half_length = palindrome[i];
                center_index = i;
            }
        }

        string palindromic_substring = "";
        if (half_length > 0) {
            ll start = center_index - half_length + 1;
            ll end = center_index + half_length - 1;
            for (ll i = start; i <= end; i += 2) {
                palindromic_substring += Temp_String[i];
            }
        }
        else {
            palindromic_substring = prototype[0];
        }
        return palindromic_substring;
    }
    else {
        return "";
    }
}

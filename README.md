# Ft_ssl

Disclaimer
----------
> In School 42, almost every project must be written according to a coding syntax standard (also known as "[Norme](./docs/norme.fr.pdf)").
>
> That's why some parts may be strange

About
-----
> We will recode part of the OpenSSL program, specifically the MD5 Hashing Algorithm.

Installation
------------
Run `make fclean && make`

Usage
-----
`./ft_ssl command [command_opts] [command_args]`

- Message Digest commands:
  * md5
    * -p: Echo stdin to stdout and append the checksum to stdout.
    * -q: Quiet mode - only the checksum is printed out. Overrides the -r option.
    * -r: Reverses the format of the output. This helps with visual diffs.
    * -s <u>string</u>: Print a checksum of the given string.
  * sha256
    * -p: Echo stdin to stdout and append the checksum to stdout.
    * -q: Quiet mode - only the checksum is printed out. Overrides the -r option.
    * -r: Reverses the format of the output. This helps with visual diffs.
    * -s <u>string</u>: Print a checksum of the given string.

### Example
```
> ./ft_ssl md5 -s "kcosta42"
MD5 ("kcosta42") = 0008107048d16472a4315fb755ce1886
```

Resources
---------
- [RFC 1321 - The MD5 Message-Digest Algorithm](https://tools.ietf.org/html/rfc1321.html)

- [RFC 6234 - US Secure Hash Algorithms](https://tools.ietf.org/html/rfc6234)

##### Project done in 2018

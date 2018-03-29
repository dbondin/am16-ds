#!/bin/bash

xmllint --format - |
  iconv -f cp1251 -t utf8 |
  sed -n '/<CharCode>/ s_^.*<CharCode>\(.*\)</CharCode>_\1_p; /<Nominal>/ s_^.*<Nominal>\(.*\)</Nominal>_\1_p; /<Name>/ s_^.*<Name>\(.*\)</Name>_\1_p; /<Value>/ s_^.*<Value>\(.*\)</Value>_\1_p;' |
  while [ true ];
  do
    A=""; read A; read B; read C; read D;
    if [ "$A" == "" ]; then
      break;
    fi;
    echo $1 $A $B $D $C;
  done

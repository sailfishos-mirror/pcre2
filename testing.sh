for i in 2 4; do
  ./perltest.sh testinput$i-perl > testoutput$i-perl
  build/pcre2test -q testinput$i-perl | \
    sed -E -e 's/Failed: error [0-9]+ at offset ([0-9]+): .*/Failed: error XXX at offset \1: XXX/' \
    > testoutput$i-pcre
done

# diff -U3 --color=always testoutput2-perl testoutput2-pcre | less -r

./perltest.sh testinput-filtered > testoutput-filtered-perl
build/pcre2test -q testinput-filtered \
  > testoutput-filtered-pcre
  
# diff -U3 --color=always testoutput-filtered-perl testoutput-filtered-pcre | less -r
use strict;
use warnings;

my $str = "abcdef";
if ($str =~ /[a-\d]/) {
    print "Match found: $&\n";
} else {
    print "No match\n";
}
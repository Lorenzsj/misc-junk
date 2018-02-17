#!/usr/bin/env perl

use strict;
use warnings;

my @dirs = grep { -d } glob '*';

foreach my $dir (@dirs) {
    opendir DIR, $dir or die "Unable to open directory $dir: $!";
    my @files = readdir DIR;
    chdir $dir;
    foreach my $file (@files) {
        next if ($file eq ".");
        next if ($file eq "..");
        my ($ext) = $file =~ /(\.[^.]+)$/;
        if ($ext eq ".zip") {
            system("unzip $file");
            system("rm $file");
            @files = readdir(DIR);
        }
        elsif ($ext eq ".tar") {
        }
        elsif ($ext eq ".gz") {
            system("tar -xvf $file"); 
        }
    }
    chdir "..";
    closedir DIR;
}

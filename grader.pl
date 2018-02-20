#!/usr/bin/env perl

use strict;
use warnings;

# regex pattern for locating archives
my $re_archive = qr/\.(zip|tar|tar\.gz|7z)$/;
my $re_src = qr/\.cpp$/;

# store all directories from current directory
my @directories = grep(-d , glob '*');
foreach (@directories) {
    opendir DIR, $_ or die "Unable to open directory $_: $!";
    chdir $_ or die "Unable to change directory to $_: $!";

    print "$_\n"; # debug
    my @archives = grep(${re_archive}, glob '*');
    if (@archives) {
        foreach (@archives) { # if archive 
            my ($ext) = $_ =~ /((\.[^.\s]+)+)$/; # parse file extension
            if ($ext eq ".zip") {
                system("unzip $_ > /dev/null 2>&1"); # suppress output
            }
            elsif ($ext eq ".tar") {
                system("tar -xvf $_");
            }
            elsif ($ext eq ".tar.gz") {
                system("tar -xvzf $_");
            }
            elsif ($ext eq ".7z") {
                system("7z e $_ > /dev/null 2>&1"); # supress output
            }
        }
    }

    system("g++ -std=c++11 *.cpp &> build.txt");

    chdir ".." or die "Unable to return to parent directory: $!";
    closedir DIR or die "Unable to close directory $_: $!";
}

=pod
    my @files = grep(${re_src}, glob '*');
    foreach (@files) {
        print "  $_\n";
    }
=cut


Name:           ansilove
Version:        4.2.1
Release:        1%{?dist}
Summary:        ANSI and ASCII art to PNG converter

License:        BSD-2-Clause
URL:            https://github.com/ansilove/ansilove
Source0:        %{url}/releases/download/%{version}/%{name}-%{version}.tar.gz

BuildRequires:  libansilove-devel
BuildRequires:  cmake
BuildRequires:  gcc

%description
AnsiLove is an ANSI and ASCII art to PNG converter, allowing to convert
ANSI and artscene-related file formats into PNG images, supporting ANSI
(.ANS), PCBoard (.PCB), Binary (.BIN), Artworx (.ADF), iCE Draw (.IDF),
Tundra (.TND) and XBin (.XB) formats.

It creates size optimized 4-bit PNG files and supports SAUCE (Standard
Architecture for Universal Comment Extentions), 80x25 and 80x50 PC fonts
(including all the 14 MS-DOS charsets), Amiga fonts, and iCE colors.

%prep
%autosetup

%build
%cmake .
%cmake_build

%install
%cmake_install

%check

%files
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1*
%license LICENSE
%doc README.md

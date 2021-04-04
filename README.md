SuperSeeker (SubcloneSeeker v2)
==============

Tumor subclone structure reconstruction across multiple samples

Introduction
============

Clonal heterogeneity is a defining feature of many tumor types. The elucidation
of the subclones that exist within tumor samples, together with the
corresponding cellular fractions, is essential to understand tumorigenesis,
relapse, and metastasis. We developed a software framework, SubcloneSeeker,
that examines somatic variation events in order to identify the underlying
subclone structure, i.e. the subclones including the normal (non-cancerous)
cells and their cellular frequencies within the tumor tissue. When multiple
tumor samples are aquired from the same patient, either via longidutinal
sampling over time, or rapid autopsy approach across many metastasis sites, it
is important to perform multi-sample joint subclone reconstruction to
understand the overall evolution history of subclones across these samples.
SuperSeeker is updated to allow for this particular function

Getting Started
---------------

Please refer to the documentation for how to get started, or run examples.

http://yiq.github.io/SubcloneSeekerDoc/
(currently on v1, pending update for v2)

Directory Structure
------------------- 

'src' directory contains source code for the core functions of SuperSeeker in
which the basic data types and logics to reconstruct super trees are defined.

'contrib' directory contains third part libraries that the project uses.

License
-------

SubcloneSeeker is distributed under MIT license.

The MIT License (MIT)

Copyright (c) 2021 Yi Qiao

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

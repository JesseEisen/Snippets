#!/usr/bin/env bash

#sed -i 's/"/\"/g' codes

summary=$(sed -n '1p' codes)
types=$(sed -n '2p' codes)
rabstract=$(sed -n '3,4p' codes)
abstract=$(sed 's/$/&\\/g' <<< "$rabstract")
Rcode=$(sed -n '6,$p' codes)
Icode=$(sed  's/$/&\\/g' <<< "$Rcode")
lineNo=`grep -n card-1 index.html | head -1|cut -b 1,2`

card="<div class=\"card card-1\"> \
<p><h2>${summary}</h2></p> \
<p class=\"abstrcat\">${abstract}</p> \
<p class=\"showcodes\"><a class=\"clicks\" href=\"#\" onclick=\"showdiv(this);return false;\">show code</a></p> \
<div class=\"sourcecode\"> \
<pre><code class=\"${types}\" >${Icode}</code></pre> \
<div class=\"btm\"> \
<a href=\"#\" class=\"btn\" onclick=\"hidediv(this);\">Hide code</a> \
</div>\
</div>\
</div>"

sed -i "$lineNo i${card}" index.html
echo "done"

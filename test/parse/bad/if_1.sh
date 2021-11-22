if { true; false; true & false; true && false; false; } then
	false
elif { true; false; true & false; true && false; false; } then
    true;
else
    if { true; false; true & false; true && false; false; } then
	true;
    fi
elif { true; false; true & false; true && false; false; } then
    true;
fi

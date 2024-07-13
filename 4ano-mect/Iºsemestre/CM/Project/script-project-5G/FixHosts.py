import os

os.popen('cp /etc/hosts /etc/hosts_old') 
hostsFile = open('/etc/hosts', 'r')

Lines = hostsFile.readlines()
hostsFile.close()

hostsFile = open('/etc/hosts', 'w')

for line in Lines:
    if line.startswith('::1 ') and ' localhost ' in line:
        line = line.replace(' localhost ', ' ')
    
    hostsFile.write(line)

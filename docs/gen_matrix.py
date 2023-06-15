import sys

if len(sys.argv) != 7:
    print("Error, invalid number of args")
    exit()

f = open(sys.argv[6], "w")

f.write('<svg xmlns="http://www.w3.org/2000/svg" width="180" height="100">\n\
  <rect width="100%" height="100%" fill="green" />\n\
  <g fill="black">\n\
    <g>\n')

arg_ind = 1
for y in range(0, 100, 20):
    f.write('      <g transform="translate(10 %i)">\n' % (y + 10))

    x_ind = 0
    for x in range(0, 180, 20):
        if sys.argv[arg_ind][x_ind] == '0':
            f.write('        <circle cx="%i" cy="0" r="9"/>\n' % x)
        else:
            f.write('        <circle cx="%i" cy="0" r="9" fill="red"/>\n' % x)

        x_ind += 1

    f.write('      </g>\n')

    arg_ind += 1

f.write('    </g>\n\
  </g>\n\
</svg>')

f.close()

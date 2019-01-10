#!/bin/python

def main():
    output = ''
    with open('../32pointsM.csv') as f:
        newYs = []
        all = f.readlines()
        for i in range(0, len(all) // 3):
            stringV = all[3*i].strip()
            stringY = all[3*i+1].strip()
            stringM = all[3*i+2].strip()
            newStringY = ''
            
            for v, y, m in zip(stringV.split(','), stringY.split(','), stringM.split(',')):
                newY = float(y) - float(v) * float(m)
                newYs.append(abs(newY))
                newStringY += '{0:.6f},'.format(newY)
            newStringY = newStringY[0:len(newStringY)-1]
            
            output += stringV + '\n' + newStringY + '\n' + stringM + '\n'

    print(output.strip())

    # print(sorted(newYs, reverse=True))

if __name__ == '__main__':
    main()
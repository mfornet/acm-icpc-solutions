#!/usr/bin/env python2

import sys

FILENAME = 'e2.in'

class PRNG:
    def __init__(self, seed): self.seed = seed

    def _random(self):
        M, A = 2147483647, 16807
        Q, R = M // A, M % A
        self.seed = A * (self.seed % Q) - R * (self.seed // Q)
        if self.seed <= 0: self.seed += M
        return self.seed

    def random(self):
        return self._random() * 1.0 / 2147483647

    def randrange(self, n):
        return self._random() % n

    def randint(self, start, end):
        res = start + int(self._random() % (end - start + 1))
        assert start <= res <= end, "%d %d %d" % (start, res, end)
        return res

    def choice(self, seq):
        return seq[self.randint(0, len(seq) - 1)]

    def shuffle(self, data):
        n = len(data)
        for i in xrange(n):
            j = self.randint(i, n-1)
            data[i], data[j] = data[j], data[i]

class Checksum:
    def __init__(self): self.chk = 47

    def add(self, *xs):
        for x in xs:
            assert isinstance(x, (int, long))
            self.chk = (42 * self.chk + x) % 123455678901

    def check(self, expected, f):
        if self.chk != expected:
            f.truncate(0)
            raise RuntimeError("Internal error, something went wrong. Expected checksum %d got %d" % (expected, self.chk) )

random = PRNG(4747)
chk = Checksum()


sys.stdout = fh = open(FILENAME, 'w')

magic = [(-730757028,-730757014,1,897),(505126523,505126532,-1,885),(-103141165,
-103141137,1,913),(320278289,320278319,-1,700),(-158860102,-158860080,-1,622),(-
862737183,-862737159,1,287),(313382670,313382710,-1,906),(501467523,501467564,-1
,194),(731018465,731018488,-1,241),(-267304510,-267304468,-1,382),(475988544,
475988572,1,922),(999898330,1000000000,-1,282084),(-558883904,-558883890,-1,825)
,(501467519,501467559,1,621),(-492360895,-492360874,-1,363),(245903936,245903977
,-1,423),(-200160168,-200160144,-1,384),(-951420296,-951420289,-1,175),(
121934716,121934725,-1,677),(534164356,534164394,-1,448),(-555957657,-555957654,
1,646),(-106877713,-106877707,-1,159),(873538803,873538828,-1,696),(-707997508,-
707997490,-1,445),(-932880492,-932880468,1,201),(-387508058,-387508036,-1,282),(
272530231,272530260,1,20),(-666682314,-666682306,-1,820),(-871627354,-871627325,
1,351),(475988545,475988576,-1,572),(320278287,320278313,1,983),(611972340,
611972359,1,547),(-755711376,-755711356,-1,357),(-138836842,-138836818,1,681),(
575504700,575504715,1,42),(-707997510,-707997494,1,890),(-91115568,-91115537,-1,
659),(-237148595,-237148559,-1,752),(295618280,295618305,1,951),(965786361,
965786371,-1,259),(-623016997,-623016989,-1,778),(-431494585,-431494565,1,226),(
93162297,93162332,1,27),(-495831554,-495831524,1,557),(104136096,104136123,-1,
546),(-492360897,-492360879,1,550),(-666682316,-666682309,1,429),(-108022039,
-108022002,1,649),(980025309,980025323,1,821),(-772010935,-772010912,1,892),(
-267304513,-267304473,1,682),(-558883906,-558883892,1,336),(797016704,797016739,
-1,696),(104136094,104136117,1,410),(121934712,121934721,1,347),(360388143,
360388163,1,874),(-571992437,-571992409,-1,590),(980984630,980984665,1,734),(
436589811,436589814,1,51),(436589815,436589822,-1,469),(-91115570,-91115543,1,83
),(955035748,955035772,-1,347),(-571992438,-571992411,1,640),(-507386838,-
507386800,-1,325),(-564402664,-564402630,-1,925),(-513725507,-513725485,1,349),(
-333026090,-333026083,-1,115),(272768394,272768404,-1,640),(471781789,471781796,
-1,827),(52145741,52145755,1,647),(461820502,461820522,1,992),(-741280491,-
741280465,1,548),(-1000000000,1000000000,-1,95287),(-72777143,-72777123,1,377),(
611972340,611972360,-1,370),(52145742,52145757,-1,661),(-887012437,-887012409,1,
485),(833810088,833810117,1,724),(-755711376,-755711358,1,489),(946706083,
946706094,-1,446),(385042385,385042412,1,4),(-741280489,-741280461,-1,324),(
833810090,833810119,-1,865),(-399602894,-399602888,-1,74),(260595832,260595841,1
,335),(-951420297,-951420292,1,628),(980025311,980025325,-1,573),(93162297,
93162336,-1,909),(758691199,758691216,-1,474),(-655626836,-655626828,1,843),(
81320786,81320818,-1,621),(81320784,81320814,1,199),(731018465,731018485,1,357),
(-513725505,-513725481,-1,894),(999907625,999907627,-1,1927770),(-495831553,-
495831522,-1,569),(385042386,385042416,-1,276),(295618284,295618312,-1,74),(-
103141162,-103141134,-1,607),(-555957657,-555957654,-1,307),(-507386839,-
507386804,1,141),(-86816481,-86816456,1,374),(513468078,513468117,1,835),(
758691195,758691211,1,952),(999999973,1000000000,-1,67240),(-180544983,-
180544948,-1,281),(955035744,955035766,1,593),(-108022039,-108022001,-1,949),(-
200160172,-200160148,1,858),(-871627354,-871627321,-1,602),(-781093052,-
781093043,-1,83),(406701021,406701043,-1,298),(980984632,980984671,-1,516),(-
621044040,-621044034,-1,554),(-998614574,-998614562,-1,552),(25755899,25755904,1
,729),(425818973,425818998,1,488),(-862737182,-862737155,-1,389),(360388145,
360388167,-1,166),(404507560,404507580,-1,256),(250592005,250592042,-1,965),(
461820503,461820523,-1,364),(-72777142,-72777119,-1,912),(-986533409,-986533389,
-1,886),(534378402,534378434,1,370),(-180544986,-180544952,1,376),(797016700,
797016732,1,698),(999898213,1000000000,1,375944),(8974799,8974838,-1,13),(
260595836,260595845,-1,118),(-866921499,-866921490,-1,40),(471781788,471781795,1
,187),(-863824302,-863824262,-1,642),(-564402666,-564402633,1,32),(-897809385,-
897809375,1,803),(946706083,946706092,1,668),(-237148599,-237148565,1,459),(-
1000000000,1000000000,1,98272),(404507560,404507578,1,833),(-633895632,-
633895590,-1,472),(-225916114,-225916104,-1,683),(739729543,739729580,1,233),(-
781093056,-781093047,1,550),(-621044041,-621044037,1,514),(-431494583,-431494562
,-1,951),(-983823085,-983823058,-1,956),(250592004,250592038,1,700),(280277814,
280277846,1,190),(823094142,823094157,1,374),(272530234,272530267,-1,123),(
507614443,507614454,-1,548),(-655626834,-655626823,-1,624),(507614439,507614449,
1,353),(25755900,25755908,-1,922),(398521108,398521135,-1,766),(-138836842,-
138836818,-1,633),(-652892908,-652892870,-1,830),(-932880491,-932880464,-1,825),
(425818976,425819004,-1,598),(873538801,873538824,1,873),(534164354,534164388,1,
113),(-225916115,-225916107,1,124),(-816151959,-816151944,1,827),(-816151956,-
816151940,-1,602),(534378403,534378439,-1,903),(-102132182,-102132164,-1,646),(-
730757026,-730757009,-1,542),(-1000000000,-1000000000,-1,90179),(739729544,
739729584,-1,956),(-983823088,-983823064,1,479),(878428501,878428528,1,562),(-
607941645,-607941625,-1,213),(-102132185,-102132167,1,517),(567823807,567823821,
1,526),(878428505,878428536,-1,223),(-623016997,-623016990,1,702),(-863824304,-
863824264,1,945),(-998614574,-998614566,1,487),(999999998,1000000000,1,1883447),
(272768393,272768400,1,932),(-633895632,-633895594,1,557),(313382669,313382707,1
,682),(-399602897,-399602893,1,18),(562378115,562378148,1,56),(406701020,
406701038,1,867),(513468078,513468119,-1,409),(999907625,999907652,1,63609),(
575504700,575504716,-1,262),(-866921499,-866921494,1,290),(-772010934,-772010909
,-1,856),(505126521,505126530,1,464),(398521107,398521133,1,964),(567823810,
567823825,-1,219),(562378119,562378154,-1,715),(-897809381,-897809367,-1,478),(-
387508058,-387508037,1,108),(-986533413,-986533396,1,680),(8974797,8974832,1,739
),(965786358,965786367,1,983),(-86816479,-86816454,-1,690),(823094144,823094162,
-1,555),(-106877716,-106877711,1,356),(245903933,245903973,1,147),(280277814,
280277850,-1,586),(-887012434,-887012403,-1,506),(-158860106,-158860087,1,168),(
-607941648,-607941632,1,695),(-333026093,-333026086,1,753),(-652892912,-
652892877,1,875)]

q = []
for a, b, c, d in magic:
    if b < a: raise ValueError((a, b, c, d))
    q.extend((random.randint(a, b), c) for i in xrange(d))
random.shuffle(q)
print 1
print
chk.add(len(q))
print len(q)
for a, b in q:
    chk.add(a, b)
    print a, b


chk.check(42069076972, fh)

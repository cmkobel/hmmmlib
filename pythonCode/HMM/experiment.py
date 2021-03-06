#
# A simple experiment that computes p(x,z) and log p(x,z) for increasing x (and z) in
# order to when p(x,z) becomes to small to be represented. For the 7-state model this
# is when |x| = |z| = 530.
#

from hmm import hmm

m = hmm("hmm-7-state.txt")

x = m.str_to_obs("TGAGTATCACTTAGGTCTATGTCTAGTCGTCTTTCGTAATGTTTGGTCTTGTCACCAGTTATCCTATGGCGCTCCGAGTCTGGTTCTCGAAATAAGCATCCCCGCCCAAGTCATGCACCCGTTTGTGTTCTTCGCCGACTTGAGCGACTTAATGAGGATGCCACTCGTCACCATCTTGAACATGCCACCAACGAGGTTGCCGCCGTCCATTATAACTACAACCTAGACAATTTTCGCTTTAGGTCCATTCACTAGGCCGAAATCCGCTGGAGTAAGCACAAAGCTCGTATAGGCAAAACCGACTCCATGAGTCTGCCTCCCGACCATTCCCATCAAAATACGCTATCAATACTAAAAAAATGACGGTTCAGCCTCACCCGGATGCTCGAGACAGCACACGGACATGATAGCGAACGTGACCAGTGTAGTGGCCCAGGGGAACCGCCGCGCCATTTTGTTCATGGCCCCGCTGCCGAATATTTCGATCCCAGCTAGAGTAATGACCTGTAGCTTAAACCCACTTTTGGCCCAAACTAGAGCAACAATCGGAATGGCTGAAGTGAATGCCGGCATGCCCTCAGCTCTAAGCGCCTCGATCGCAGTAATGACCGTCTTAACATTAGCTCTCAACGCTATGCAGTGGCTTTGGTGTCGCTTACTACCAGTTCCGAACGTCTCGGGGGTCTTGATGCAGCGCACCACGATGCCAAGCCACGCTGAATCGGGCAGCCAGCAGGATCGTTACAGTCGAGCCCACGGCAATGCGAGCCGTCACGTTGCCGAATATGCACTGCGGGACTACGGACGCAGGGCCGCCAACCATCTGGTTGACGATAGCCAAACACGGTCCAGAGGTGCCCCATCTCGGTTATTTGGATCGTAATTTTTGTGAAGAACACTGCAAACGCAAGTGGCTTTCCAGACTTTACGACTATGTGCCATCATTTAAGGCTACGACCCGGCTTTTAAGACCCCCACCACTAAATAGAGGTACATCTGA")

z = m.str_to_states("4444432132132132132132132132132132132132132132132132132132132132132132144444444445675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675674321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321321432132132132132132132132144445675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675675674444444567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567567443213213213213213213213213213213213213213213213213213213213213213213213213213213213213213213213214321321321321321321321321321321321321321321321321321321321321321")

for i in range(1,len(x)):
    print ()
    print (i)
    print ("p(x,z) = ", m.joint_prob(x[:i], z[:i]))
    print ("log p(x,z) = ", m.log_joint_prob(x[:i], z[:i]))



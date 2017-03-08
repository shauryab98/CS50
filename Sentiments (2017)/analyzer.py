import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.posWords = set()
        self.negWords = set()
        postext = open(positives, 'r')
        for line in postext:
            if(len(line.lower().rstrip("\n")) > 0 and line[0] != ";"):
                self.posWords.add(line.lower().rstrip("\n"))
        postext.close()
        negtext = open(negatives, 'r')
        for line in negtext:
            if(len(line) > 0 and line[0] != ";"):
                self.negWords.add(line.lower().rstrip("\n"))
        negtext.close()
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        words = tokenizer.tokenize(text)
        score = 0
        for word in words:
            if word in self.posWords:
                score = score + 1
            elif word in self.negWords:
                score = score - 1
        return score

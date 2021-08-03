//source: http://www.cplusplus.com/forum/lounge/79437/

/*!
 * Hello world! application
 * 
 * \file hello.cpp
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

/*!
 * Dispay message.
 */
void displayMessage();

/*!
 * Sentence type
 *
 * Type of sentence, used to decide how to terminate sentence.
 */
enum ESentenceType {
    eStatement,
    eExclamation,
    sQuestion,
    eCommand
};

/*!
 * Utility class to prevent unintended copying of class instances.
 */
class nonCopyable {
protected:
    nonCopyable() {
    }

    ~nonCopyable() {
    }

private:
    nonCopyable(const nonCopyable&);
    const nonCopyable& operator=(const nonCopyable&);
};

/*!
 * Utility function to obtain punctuation mark to end sentence
 * of specified type.
 */
inline char getPunctionMark(ESentenceType sentenceType) {
    char puncMark = '.';
    switch(sentenceType) {
        case eStatement  : puncMark = '.'; break;
        case eExclamation: puncMark = '!'; break;
        case sQuestion   : puncMark = '?'; break;
        case eCommand    : puncMark = '.'; break;
        default: {
            // should never get here
            assert(false);
        }
    }
    return puncMark;
}

/*!
 * Utility class for creation of instances.
 */
template<typename TElem>
class Creatable {
protected:
    Creatable() {
    }

    virtual ~Creatable() {
        clear();
    }

public:
    static TElem* create() {
        TElem* e = new TElem;
        return e;
    }

    void free() {
        delete this;
    }

    virtual void clear() {
    }
};

template<typename TElem, typename TParam>
class CreatableParam {
protected:
    CreatableParam() {
    }

    virtual ~CreatableParam() {
    }

public:
    static TElem* create(TParam p) {
        TElem* e = new TElem;
        e->initialize(p);
        return e;
    }

    void free() {
        finalize();
        delete this;
    }

    virtual void initialize(TParam /*p*/) {
    }

    virtual void finalize() {
        clear();
    }

    virtual void clear() {
    }
};

/*!
 * Base class for displayable content
 */
class DisplayElem
: public nonCopyable {
protected:
    DisplayElem() {
    }

    virtual ~DisplayElem() {
    }

public:
    virtual void display(std::ostream& os) const = 0;
};

/*!
 * STL algorithm for displaying elements
 */
class Displayer
: public std::unary_function<void, const DisplayElem*> {
private:
    std::ostream& m_os;
    char   m_sep;
    size_t m_count;

public:
    Displayer(std::ostream& os, char sep = '\0')
    : m_os(os)
    , m_sep(sep)
    , m_count(0) {
    }

    ~Displayer() {
    }

    void operator()(const DisplayElem* e) {
        if(('\0' != m_sep) && (0 < m_count)) {
            m_os << m_sep;
        }
        e->display(m_os);
        ++m_count;
    }
};

/*!
 * STL algorithm for freeing display elements
 */
template <typename TElem>
class Freer
: public std::unary_function<void, TElem*> {
public:
    void operator()(TElem* e) {
        e->free();
    }
};

/*!
 * Display element for letter.
 *
 * The letter is the fundamental element: it has no substructure.
 */
class Letter
: public DisplayElem
, public CreatableParam<Letter, char> {
private:
    char m_ch;

protected:
    /*virtual*/ ~Letter() {
    }

public:
    Letter() : m_ch('\0') {
    }

    void initialize(char ch) {
        m_ch = ch;
    }

    void finalize() {
        m_ch = '\0';
    }

    void display(std::ostream& os) const {
        os << m_ch;
        // no endLetter()
    }
};

/*!
 * Display element for word.
 *
 * A word is a sequence of letters.
 */
class Word
: public DisplayElem
, public Creatable<Word> {
private:
    std::vector<Letter*> m_letters;

protected:
    /*virtual*/ ~Word() {
        clear();
    }

public:
    Word() {
    }

    void clear() {
        std::for_each(m_letters.begin(), m_letters.end(), Freer<Letter>());
        m_letters.clear();
    }

    void addLetter(Letter* s) {
        m_letters.push_back(s);
    }

    /*virtual*/ void display(std::ostream& os) const {
        std::for_each(m_letters.begin(), m_letters.end(), Displayer(os));
        // no endLetter()
    }
};

/*!
 * Display element for sentence.
 *
 * A sentence is a sequence of words.
 */
class Sentence
: public DisplayElem
, public CreatableParam<Sentence, ESentenceType> {
private:
    std::vector<Word*> m_words;

    ESentenceType m_sentenceType;

protected:
    /*virtual*/ ~Sentence() {
        clear();
    }

    void endSentence(std::ostream& os) const {
        const char puncMark = getPunctionMark(m_sentenceType);
        os << puncMark;
    }

public:
    Sentence()
    : m_sentenceType(eStatement) {
    }

    void initialize(ESentenceType sentenceType) {
        m_sentenceType = sentenceType;
    }

    void finalize() {
        m_sentenceType = eStatement;
    }

    void clear() {
        std::for_each(m_words.begin(), m_words.end(), Freer<Word>());
        m_words.clear();
    }

    void addWord(Word* w) {
        m_words.push_back(w);
    }

    void display(std::ostream& os) const {
        std::for_each(m_words.begin(), m_words.end(), Displayer(os, ' '));
        endSentence(os);
    }
};

/*!
 * Display element for message.
 *
 * A message is a sequence of sentences.
 */
class Message
: public DisplayElem
, public Creatable<Message> {
private:
    std::vector<Sentence*> m_sentences;

protected:
    /*virtual*/ ~Message() {
        clear();
    }

    void endMessage(std::ostream& os) const {
        os << std::endl;
    }

public:
    Message() {
    }

    void clear() {
        std::for_each(m_sentences.begin(), m_sentences.end(), Freer<Sentence>());
        m_sentences.clear();
    }

    void addSentence(Sentence* s) {
        m_sentences.push_back(s);
    }

    void display(std::ostream& os) const {
        std::for_each(m_sentences.begin(), m_sentences.end(), Displayer(os, ' '));
        endMessage(os);
    }
};

/*!
 * Main entrance point.
 */
int main() {
    displayMessage();
    return 0;
}

/*!
 * Display message.
 */
void displayMessage() {
    Word* first_word = Word::create();
    first_word->addLetter(Letter::create('H'));
    first_word->addLetter(Letter::create('e'));
    first_word->addLetter(Letter::create('l'));
    first_word->addLetter(Letter::create('l'));
    first_word->addLetter(Letter::create('o'));

    Word* second_word = Word::create();
    second_word->addLetter(Letter::create('w'));
    second_word->addLetter(Letter::create('o'));
    second_word->addLetter(Letter::create('r'));
    second_word->addLetter(Letter::create('l'));
    second_word->addLetter(Letter::create('d'));

    Sentence* sentence = Sentence::create(eExclamation);
    sentence->addWord(first_word);
    sentence->addWord(second_word);

    Message* message = Message::create();
    message->addSentence(sentence);

    message->display(std::cout);

    message->free();
    // sentences, etc freed by parent
}

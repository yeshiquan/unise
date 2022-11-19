#pragma once

#include "query.h"
#include <vector>

namespace mmse {

class BooleanScorer2 : public Scorer {
public:
    BooleanScorer2();
    ~BooleanScorer2();
    BooleanScorer2(std::vector<Scorer*>& optional, std::vector<Scorer*>& required, std::vector<Scorer*>& prohibited);

    BooleanScorer2(BooleanScorer2 const&) = delete;             // Copy construct
    BooleanScorer2(BooleanScorer2&&) = delete;                  // Move construct
    BooleanScorer2& operator=(BooleanScorer2 const&) = delete;  // Copy assign
    BooleanScorer2& operator=(BooleanScorer2 &&) = delete;      // Move assign   

    void set_min_should_match(uint32_t n) { _min_should_match = n; }      
    void build();      

    DocId next_doc() override; 
    DocId skip_to(DocId target) override;   
    DocId doc() const override; 
    std::vector<std::string> explain() const override;
private:
    Scorer* _make_counting_sum_scorer();
    Scorer* _make_should(std::vector<Scorer*>&, uint32_t);
    Scorer* _make_must(std::vector<Scorer*>&);
    Scorer* _make_must_plus_should(std::vector<Scorer*>&, std::vector<Scorer*>&);
    Scorer* _make_must_plus_mustnot(std::vector<Scorer*>&, std::vector<Scorer*>&);
private:
    Scorer* _counting_sum_scorer = nullptr; // 领头的scorer
    std::vector<Scorer*> _optional_scorers;
    std::vector<Scorer*> _required_scorers;
    std::vector<Scorer*> _prohibited_scorers;
    uint32_t _min_should_match = 0; // should最少应该满足的个数
};

} // namespace
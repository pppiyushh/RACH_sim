class Cell
{
    public:

    Cell();

    private:
        std::vector<UE> ue_list_;
        Channel channel_;
        
    // SSB will be sent after each 5 slot
    std::uint64_t SSUB_frequency = 5; 

    void schedule_SSBs();
        


};
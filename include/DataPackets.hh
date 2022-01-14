#ifndef __DATAPACKETS_hh
#define __DATAPACKETS_hh

#include "TObject.h"

class FebexData : public TObject {
	
public:

	FebexData();
	FebexData( unsigned long long t,
			  std::vector<unsigned short> tr,
			  unsigned short qi, Float16_t qh, float qf,
			  unsigned char s, unsigned char b, unsigned char c,
			  bool th, bool v, bool f );
	~FebexData();

	inline unsigned long long	GetTime() { return time; };
	inline unsigned short		GetTraceLength() { return trace.size(); };
	inline unsigned short		GetQint() { return Qint; };
	inline Float16_t			GetQhalf() { return Qhalf; };
	inline float				GetQfloat() { return Qfloat; };
	inline unsigned char		GetSfp() { return sfp; };
	inline unsigned char		GetBoard() { return board; };
	inline unsigned char		GetChannel() { return ch; };
	inline float				GetEnergy() { return energy; };
	inline bool					IsOverThreshold() { return thres; };
	inline bool					IsVeto() { return veto; };
	inline bool					IsFail() { return fail; };
	inline std::vector<unsigned short> GetTrace() { return trace; };
	inline unsigned short		GetSample( unsigned int i = 0 ) {
		if( i >= trace.size() ) return 0;
		return trace.at(i);
	};
	
	inline void	SetTime( unsigned long long t ) { time = t; };
	inline void	SetTrace( std::vector<unsigned short> t ) { trace = t; };
	inline void AddSample( unsigned short s ) { trace.push_back(s); };
	inline void	SetQint( unsigned short q ) { Qint = q; };
	inline void	SetQhalf( Float16_t q ) { Qhalf = q; };
	inline void	SetQfloat( float q ) { Qfloat = q; };
	inline void SetSfp( unsigned char s ){ sfp = s; };
	inline void SetBoard( unsigned char b ){ board = b; };
	inline void	SetChannel( unsigned char c ) { ch = c; };
	inline void SetEnergy( float e ){ energy = e; };
	inline void SetThreshold( bool t ){ thres = t; };
	inline void SetVeto( bool v ){ veto = v; };
	inline void SetFail( bool f ){ fail = f; };

	inline void ClearTrace() { trace.clear(); };
	void ClearData();

protected:
	
	unsigned long long			time;
	std::vector<unsigned short>	trace;
	unsigned short				Qint;		///< Charge from firmware as 16-bit integer
	Float16_t					Qhalf;		///< Charge from firmware as 16-bit float
	float						Qfloat;		///< Charge from firmware as 32-bit float
	unsigned char				sfp;		///< SFP ID of the event
	unsigned char				board;		///< board ID of the event
	unsigned char				ch;			///< channel ID of the event
	bool						thres;		///< is the energy over threshold?
	bool						veto;		///< veto bit from data stream
	bool						fail;		///< fail bit from data stream
	float						energy;

	
	ClassDef( FebexData, 1 )
	
};

class InfoData : public TObject {
	
public:

	InfoData();
	InfoData( unsigned long long t, unsigned char s, unsigned char b, unsigned char m );
	~InfoData();
	
	inline unsigned long long	GetTime(){ return time; };
	inline unsigned char 		GetCode(){ return code; };
	inline unsigned char		GetSfp(){ return sfp; };
	inline unsigned char		GetBoard(){ return board; };

	inline void SetTime( unsigned long long t ){ time = t; };
	inline void SetCode( unsigned char c ){ code = c; };
	inline void SetSfp( unsigned char s ){ sfp = s; };
	inline void SetBoard( unsigned char b ){ board = b; };

	void ClearData();

protected:
	
	unsigned long long	time;	///< timestamp of info event
	unsigned char		code;	///< code here represents which information timestamp we have
	unsigned char		sfp;	///< SFP ID of the event
	unsigned char		board;	///< board ID of the event
	/// code = 20 is external pulser event for whatever reason
	/// code = 21 is EBIS proton timestamp
	/// code = 22 is T1 timestamp

	
	ClassDef( InfoData, 1 )
	
};

class DataPackets : public TObject {
	
public:
	
	inline bool	IsFebex() { return febex_packets.size(); };
	inline bool	IsInfo() { return info_packets.size(); };
	
	void SetData( FebexData *data );
	void SetData( InfoData *data );

	// These methods are not very safe for access
	inline FebexData* GetFebexData() { return &febex_packets.at(0); };
	inline InfoData* GetInfoData() { return &info_packets.at(0); };
	
	// Complicated way to get the time...
	unsigned long long GetTime();
	UInt_t GetTimeMSB();
	UInt_t GetTimeLSB();

	void ClearData();

protected:
	
	std::vector<FebexData>	febex_packets;
	std::vector<InfoData>	info_packets;

	ClassDef( DataPackets, 1 )

};


#endif

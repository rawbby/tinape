#pragma once

#include "log.h"
#include "utility.h"

#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>

class UDP_Socket
{
protected:
  SDLNet_DatagramSocket* handle;

public:
  UDP_Socket() = default;

  inline bool Init(const char* host, int port, int resolve_timeout_ms = 5000)
  {
    const auto address = SDLNet_ResolveHostname(host);
    if (SDLNet_WaitUntilResolved(address, resolve_timeout_ms) < 0) {
      SDL_Log("SDLNet_WaitUntilResolved failed: %s\n", SDL_GetError());
      return false;
    }

    handle = SDLNet_CreateDatagramSocket(address, port);
    if (!handle) {
      SDL_Log("SDLNet_CreateDatagramSocket failed: %s\n", SDL_GetError());
      return false;
    }

    return true;
  }

  inline void PollDatagram(auto callback)
  {
    SDLNet_Datagram* datagram = nullptr;

    do {
      if (SDLNet_ReceiveDatagram(handle, &datagram)) {
        Log("UDP socket failed at system level: %s\n", SDL_GetError());
        SoftExit();
        return;
      }

      if (!datagram)
        return;

      callback(datagram);
      SDLNet_DestroyDatagram(datagram);
    } while (true);
  }

  ~UDP_Socket()
  {
    if (handle)
      SDLNet_DestroyDatagramSocket(handle);
  }
};

class TCP_Client
{
protected:
  SDLNet_StreamSocket* handle;

public:
  TCP_Client() = default;

  inline bool Init(const char* host, int port, int resolve_timeout_ms = 5000)
  {
    const auto address = SDLNet_ResolveHostname(host);
    if (SDLNet_WaitUntilResolved(address, resolve_timeout_ms) < 0) {
      SDL_Log("SDLNet_WaitUntilResolved failed: %s\n", SDL_GetError());
      return false;
    }

    handle = SDLNet_CreateClient(address, port);
    if (!handle) {
      SDL_Log("SDLNet_CreateClient failed: %s\n", SDL_GetError());
      return false;
    }

    return true;
  }

  ~TCP_Client()
  {
    if (handle)
      SDLNet_DestroyStreamSocket(handle);
  }
};

class TCP_Server
{
protected:
  SDLNet_Server* handle;

public:
  TCP_Server() = default;

  inline bool Init(const char* host, int port, int resolve_timeout_ms = 5000)
  {
    const auto address = SDLNet_ResolveHostname(host);
    if (SDLNet_WaitUntilResolved(address, resolve_timeout_ms) < 0) {
      SDL_Log("SDLNet_WaitUntilResolved failed: %s\n", SDL_GetError());
      return false;
    }

    handle = SDLNet_CreateServer(address, port);
    if (!handle) {
      SDL_Log("SDLNet_CreateServer failed: %s\n", SDL_GetError());
      return false;
    }

    return true;
  }

  ~TCP_Server()
  {
    if (handle)
      SDLNet_DestroyServer(handle);
  }
};

class Network
{
public:
  Network() = default;

  inline bool Init()
  {
    if (SDLNet_Init()) {
      SDL_Log("SDLNet_Init failed: %s\n", SDL_GetError());
      return false;
    }

    return true;
  }

  ~Network()
  {
    SDLNet_Quit();
  }
};

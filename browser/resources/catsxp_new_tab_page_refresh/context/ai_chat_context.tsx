/* Copyright (c) 2020 The Catsxp Authors. All rights reserved. */

import * as React from 'react'

import { newConversation } from '../../../../components/ai_chat/resources/page/api/bind_conversation'
import bindAiChatWebUiServices from '../../../../components/ai_chat/resources/page/api/bind_webui_services'
import {
  ActiveChatContext,
  SelectedChatDetails,
} from '../../../../components/ai_chat/resources/page/state/active_chat_context'
import { AIChatProvider } from '../../../../components/ai_chat/resources/page/state/ai_chat_context'
import { ConversationProvider } from '../../../../components/ai_chat/resources/page/state/conversation_context'
import '../../../../components/ai_chat/resources/common/strings'

export default function AIChatContextsProvider(props: {
  children: React.ReactNode
}) {
  const aiChatBindings = React.useMemo(bindAiChatWebUiServices, [])

  const conversationDetails = React.useMemo<SelectedChatDetails>(() => {
    const conversationBindings = newConversation(aiChatBindings.api)
    return {
      ...conversationBindings,
      selectedConversationId: undefined,
      updateSelectedConversationId: () => {},
      openMainConversation: () => {},
      createNewConversation: () => {},
      isMainConversation: false,
    }
  }, [])

  return (
    <AIChatProvider
      api={aiChatBindings.api}
      // Conversation entries are not rendered in this WebUI
      conversationEntriesComponent={() => <></>}
    >
      <ActiveChatContext.Provider value={conversationDetails}>
        <ConversationProvider
          {...conversationDetails}
          isNTPWidget
        >
          {props.children}
        </ConversationProvider>
      </ActiveChatContext.Provider>
    </AIChatProvider>
  )
}

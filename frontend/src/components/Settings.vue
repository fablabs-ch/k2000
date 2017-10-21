<template>
  <div>

    <v-btn color="primary" @click="tare()">Tare</v-btn>
    <v-btn color="error" @click="stop()">Stop</v-btn>
    Config: {{ config }}

    <v-snackbar :timeout=2000
                :top=true
                :vertical=true
                v-model="snackbar">
      {{ snacktext }}
      <v-btn flat color="pink" @click.native="snackbar = false">Close</v-btn>
    </v-snackbar>
  </div>
</template>

<script>
export default {
  name: 'settings',
  data () {
    return {
      snackbar: false,
      snacktext: '',
      config: []
    }
  },
  methods: {
    tare () {
      this.$http.post('api/command/tare').then(response => {
        this.notify('Tare sent')
      }, response => {
        this.notify('Error when trying to tare')
      })
    },
    stop () {
      this.$http.post('api/command/stop').then(response => {
        this.notify('Stop sent')
      }, response => {
        this.notify('Error when trying to stop')
      })
    },
    notify (message) {
      this.snacktext = message
      this.snackbar = true
    }
  },
  mounted () {
    this.$http.get('api/config/').then(response => {
      this.config = response.data
    }, response => {
      this.notify('Impossible to load the config')
    })
  }
}
</script>

<style>

</style>

